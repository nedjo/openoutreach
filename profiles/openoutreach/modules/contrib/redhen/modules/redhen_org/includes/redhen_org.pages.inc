<?php

/**
 * @file
 * Page callbacks for redhen organizations.
 */

module_load_include('inc', 'redhen', 'includes/redhen.forms');

/**
 * Page callback for org overview page.
 */
function redhen_org_page() {

  // Setup the header for both the query and table.
  $header = array(
    'type' => array(
      'field' => 'type',
      'type' => 'property',
      'data' => 'Type',
      'sort' => 'asc',
      'specifier' => 'type',
    ),
    'label' => array(
      'field' => 'label',
      'type' => 'property',
      'data' => 'Name',
      'sort' => 'asc',
      'specifier' => 'label',
    ),
    'updated' => array(
      'field' => 'updated',
      'type' => 'property',
      'data' => 'Updated',
      'sort' => 'desc',
      'specifier' => 'updated',
    ),
  );

  $header['operations'] = array('data' => t('Operations'));

  // Need to ensure the query doesn't execute when posing the form.
  $result = FALSE;
  if (!isset($_POST['form_id'])) {
    $bundle = isset($_GET['bundle']) ? $_GET['bundle'] : '';
    $properties = isset($_GET['properties']) ? $_GET['properties'] : array();
    $fields = isset($_GET['fields']) ? $_GET['fields'] : array();
    $result = redhen_filter_query('redhen_org', $header, $bundle, $properties, $fields);
  }

  $orgs = array();
  $rows = array();
  if ($result) {
    $orgs = redhen_org_load_multiple(array_keys($result['redhen_org']));

    if (!empty($orgs)) {
      $destination = drupal_get_destination();
      foreach ($orgs as $org) {
        $uri = entity_uri('redhen_org', $org);
        $redhen_org_type = redhen_org_type_load($org->type);

        $data = array(
          'type' => check_plain($redhen_org_type->label),
          'label' => array(
            'data' => array(
              '#type' => 'link',
              '#title' => $org->label,
              '#href' => $uri['path'],
            ),
          ),
          'updated' => redhen_format_date($org->updated, 'short'),
        );

        $row_classes = array();
        // Set a class for the row depending if the org is active or archived.
        $row_classes[] = $org->redhen_state == REDHEN_STATE_ACTIVE ? 'active' : 'archived';

        $rows[$org->org_id] = array(
          'data' => $data,
          'class' => $row_classes,
        );

        // Build a list of all the accessible operations for the current org.
        $ops = array();
        if (redhen_org_access('update', $org)) {
          $ops['edit'] = array(
            'title' => t('edit'),
            'href' => $uri['path'] . '/view/edit',
            'query' => $destination,
          );
        }
        if (redhen_org_access('delete', $org)) {
          $ops['delete'] = array(
            'title' => t('delete'),
            'href' => $uri['path'] . '/view/delete',
            'query' => $destination,
          );
        }
        if (count($ops) > 1) {
          // Render an unordered list of operations links.
          $rows[$org->org_id]['data']['operations'] = array(
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
          $rows[$org->org_id]['data']['operations'] = array(
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
  }

  return array(
    'form' => drupal_get_form('redhen_filter_form', 'redhen_org'),
    'orgs' => array(
      '#theme' => 'redhen_org_list',
      '#orgs' => $orgs,
      '#header' => $header,
      '#rows' => $rows,
    ),
  );
}

/**
 * Page callback for adding an organization.
 *
 * @param string $type
 *   The type of organization to return a form for.
 */
function redhen_org_types_list_page($type = 'default') {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  // Bypass the redhen_org/add listing if only one contact type is available.
  if (count($content) == 1) {
    $item = array_shift($content);
    drupal_goto($item['href']);
  }

  $render = array(
    '#theme' => 'redhen_org_add_list',
    '#content' => $content,
  );

  return $render;
}

/**
 * Page callback for adding an organization.
 *
 * @param $type
 *
 * @return array|mixed
 */
function redhen_org_add_page($type) {
  $org = entity_get_controller('redhen_org')->create(array('type' => $type));
  return drupal_get_form('redhen_org_org_form', $org);
}

/**
 * Page callback for listing org revisions.
 *
 * @param Entity $org
 *   The org entity.
 *
 * @return array
 *   A renderable array.
 */
function redhen_org_revision_list(Entity $org) {
  drupal_set_title(t('Revisions for %title', array('%title' => $org->label())), PASS_THROUGH);

  $header = array(t('Revision'), array('data' => t('Operations'), 'colspan' => 2));
  // There is no way to list revisions using EFQ, thus use a direct SQL query.
  $revision_ids = db_select('redhen_org_revision', 'r')
    ->fields('r', array('revision_id'))
    ->condition('org_id', $org->org_id)
    ->orderBy('updated', 'DESC')
    ->execute()
    ->fetchCol();

  $rows = array();
  foreach ($revision_ids as $revision_id) {
    $row = array();
    $operations = array();
    $revision = entity_revision_load('redhen_org', $revision_id);

    if ($revision->isDefaultRevision()) {
      $row[] = array('data' => t('!date by !username', array('!date' => l(format_date($revision->updated, 'short'), "redhen/org/$revision->org_id"), '!username' => theme('username', array('account' => user_load($revision->author_uid))))),
        'class' => array('revision-default'));
      $operations[] = array('data' => drupal_placeholder(t('default revision')), 'class' => array('revision-default'), 'colspan' => 2);
    }
    else {
      $row[] = t('!date by !username', array('!date' => l(format_date($revision->updated, 'short'), "redhen/org/$revision->org_id/revisions/$revision->revision_id/view"), '!username' => theme('username', array('account' => user_load($revision->author_uid)))));
      if (redhen_org_access('edit', $revision)) {
        $operations[] = l(t('edit'), "redhen/org/$revision->org_id/revisions/$revision->revision_id/edit");
      }
      if (redhen_org_access('delete', $revision)) {
        $operations[] = l(t('delete'), "redhen/org/$revision->org_id/revisions/$revision->revision_id/delete");
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

/**
 * Autocomplete helper
 *
 * @param $string
 *  String for search
 */
function _redhen_org_autocomplete($string) {
  $matches = array();

  // build the query
  $query = new EntityFieldQuery();

  $query
    ->entityCondition('entity_type', 'redhen_org', '=')
    ->tablesort($header)
    ->pager(10);

  $query->propertyCondition('label', '%' . db_like($string) . '%', 'LIKE');

  $result = $query->execute();

  $orgs = redhen_org_load_multiple(array_keys($result['redhen_org']));

  // save the query to matches
  foreach ($orgs as $row) {
    $key = "$row->label ($row->org_id)";
    // Names containing commas or quotes must be wrapped in quotes.
    if (strpos($key, ',') !== FALSE || strpos($key, '"') !== FALSE) {
      $key = '"' . str_replace('"', '""', $key) . '"';
    }
    $matches[$key] = '<div class="redhen-autocomplete">' . check_plain($row->label) . '</div>';
  }

  // Return the result to the form in json
  drupal_json_output($matches);
}
