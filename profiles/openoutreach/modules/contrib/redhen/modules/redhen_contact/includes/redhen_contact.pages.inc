<?php

/**
 * @file
 * Page callbacks for redhen contact.
 */

module_load_include('inc', 'redhen', 'includes/redhen.forms');

/**
 * Page callback for contact overview page.
 */
function redhen_contact_page() {
  // Setup the header for both the query and table.
  $header = array(
    'type' => array(
      'field' => 'type',
      'type' => 'property',
      'data' => t('Type'),
      'specifier' => 'type',
    ),
    'first_name' => array(
      'field' => 'first_name',
      'type' => 'property',
      'data' => t('First name'),
      'specifier' => 'first_name',
    ),
    'last_name' => array(
      'field' => 'last_name',
      'type' => 'property',
      'data' => t('Last name'),
      'specifier' => 'last_name',
    ),
    'email' => array('data' => t('Email')),
    'updated' => array(
      'field' => 'updated',
      'type' => 'property',
      'data' => t('Updated'),
      'sort' => 'desc',
      'specifier' => 'updated',
    ),
  );

  $include_engagements = module_exists('redhen_engagement');
  if ($include_engagements) {
    $header['engagement_score'] = array(
      'field' => 'engagement_score',
      'type' => 'property',
      'data' => t('Engagement Score'),
      'specifier' => 'engagement_score',
    );
  }

  $header['operations'] = array('data' => t('Operations'));

  // Need to ensure the query doesn't execute when posing the form.
  $result = FALSE;
  if (!isset($_POST['form_id'])) {
    $bundle = isset($_GET['bundle']) ? $_GET['bundle'] : '';
    $properties = isset($_GET['properties']) ? $_GET['properties'] : array();
    $fields = isset($_GET['fields']) ? $_GET['fields'] : array();
    $result = redhen_filter_query('redhen_contact', $header, $bundle, $properties, $fields);
  }

  $contacts = array();
  if ($result) {
    $contacts = redhen_contact_load_multiple(array_keys($result['redhen_contact']));
  }

  $rows = array();
  if (!empty($contacts)) {
    $destination = drupal_get_destination();
    foreach ($contacts as $contact) {
      $uri = entity_uri('redhen_contact', $contact);
      $redhen_contact_type = redhen_contact_type_load($contact->type);
      $email = $contact->email();
      $rows[$contact->contact_id] = array(
        'type' => check_plain($redhen_contact_type->label),
        'first_name' => array(
          'data' => array(
            '#type' => 'link',
            '#title' => $contact->first_name,
            '#href' => $uri['path'],
          ),
        ),
        'last_name' => array(
          'data' => array(
            '#type' => 'link',
            '#title' => $contact->last_name,
            '#href' => $uri['path'],
          ),
        ),
        'email' => array(
          'data' => array(
            '#type' => 'link',
            '#title' => $email,
            '#href' => 'mailto:' . $email,
          ),
        ),
        'updated' => redhen_format_date($contact->updated, 'short'),
      );

      if ($include_engagements) {
        $rows[$contact->contact_id]['engagement_score'] = $contact->engagement_score;
      }

      // Build a list of all the accessible operations for the current contact.
      $ops = array();
      if (redhen_contact_access('update', $contact)) {
        $ops['edit'] = array(
          'title' => t('edit'),
          'href' => $uri['path'] . '/view/edit',
          'query' => $destination,
        );
      }
      if (redhen_contact_access('delete', $contact)) {
        $ops['delete'] = array(
          'title' => t('delete'),
          'href' => $uri['path'] . '/view/delete',
          'query' => $destination,
        );
      }
      if (count($ops) > 1) {
        // Render an unordered list of operations links.
        $rows[$contact->contact_id]['operations'] = array(
          'data' => array(
            '#theme' => 'links__node_operations',
            '#links' => $ops,
            '#attributes' => array('class' => array('links', 'inline')),
          ),
        );
      }
      elseif (!empty($ops)) {
        // Render the first and only operation as a link.
        $link = reset($ops);
        $rows[$contact->contact_id]['operations'] = array(
          'data' => array(
            '#type' => 'link',
            '#title' => $link['title'],
            '#href' => $link['href'],
            '#options' => array('query' => $link['query']),
          ),
        );
      }
      else {
        unset($header['operations']);
      }
    }
  }

  return array(
    'form' => drupal_get_form('redhen_filter_form', 'redhen_contact'),
    'contacts' => array(
      '#theme' => 'redhen_contact_list',
      '#contacts' => $contacts,
      '#header' => $header,
      '#rows' => $rows,
    ),
  );
}

/**
 * Page callback for adding a contact type.
 *
 * Return a list of available contacts to add or the add contact page if there's
 * only a single contact type.
 */
function redhen_contact_types_list_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  // Bypass the rehen_contact/add listing if only one contact type is available.
  if (count($content) == 1) {
    $item = array_shift($content);
    drupal_goto($item['href']);
  }
  return theme('redhen_contact_add_list', array('content' => $content));
}

/**
 * Page callback for adding a contact.
 *
 * @param string $type
 *   The redhen Contact Bundle name to create.
 *
 * @return array
 *   The contact creation form.
 */
function redhen_contact_add_page($type) {
  $contact = redhen_contact_create(array('type' => $type));
  module_load_include('inc', 'redhen_contact', 'includes/redhen_contact.forms');
  return drupal_get_form('redhen_contact_contact_form', $contact);
}

/**
 * Page callback for listing contact revisions.
 *
 * @param Entity $contact
 *   The contact entity.
 *
 * @return array
 *   A renderable array.
 */
function redhen_contact_revision_list(Entity $contact) {
  drupal_set_title(t('Revisions for %title', array('%title' => $contact->label())), PASS_THROUGH);

  $header = array(t('Revision'), array('data' => t('Operations'), 'colspan' => 2));
  // There is no way to list revisions using EFQ, thus use a direct SQL query.
  $revision_ids = db_select('redhen_contact_revision', 'r')
    ->fields('r', array('revision_id'))
    ->condition('contact_id', $contact->contact_id)
    ->orderBy('updated', 'DESC')
    ->execute()
    ->fetchCol();

  $rows = array();
  foreach ($revision_ids as $revision_id) {
    $row = array();
    $operations = array();
    $revision = entity_revision_load('redhen_contact', $revision_id);

    if ($revision->isDefaultRevision()) {
      $row[] = array('data' => t('!date by !username', array('!date' => l(format_date($revision->updated, 'short'), "redhen/contact/$revision->contact_id"), '!username' => theme('username', array('account' => user_load($revision->author_uid))))),
        'class' => array('revision-default'));
      $operations[] = array('data' => drupal_placeholder(t('default revision')), 'class' => array('revision-default'), 'colspan' => 2);
    }
    else {
      $row[] = t('!date by !username', array('!date' => l(format_date($revision->updated, 'short'), "redhen/contact/$revision->contact_id/revisions/$revision->revision_id/view"), '!username' => theme('username', array('account' => user_load($revision->author_uid)))));
      if (redhen_contact_access('edit', $revision)) {
        $operations[] = l(t('edit'), "redhen/contact/$revision->contact_id/revisions/$revision->revision_id/edit");
      }
      if (redhen_contact_access('delete', $revision)) {
        $operations[] = l(t('delete'), "redhen/contact/$revision->contact_id/revisions/$revision->revision_id/delete");
      }
    }
    $rows[] = array_merge($row, $operations);
  }

  $build['revisions_table'] = array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => $header,
  );
  return $build;
}
