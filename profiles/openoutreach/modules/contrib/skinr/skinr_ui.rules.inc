<?php

/**
 * @file
 * Admin page callbacks for Skinr module's rules.
 */

/**
 * Menu callback; displays the skinr rules listing.
 */
function skinr_rules() {
  $output = '';

  $headers = array(
    array('data' => t('Title'), 'field' => 'title'),
    array('data' => t('Type'), 'field' => 'type'),
    array('data' => t('Operations'), 'colspan' => 2)
  );

  $rules = skinr_rule_load_multiple();
  $rows = array();
  foreach ($rules as $rule) {
    $row = array(
      check_plain($rule->title),
      check_plain($rule->rule_type),
      l(t('edit'), 'admin/structure/skinr/rules/'. $rule->rid . '/edit'),
      l(t('delete'), 'admin/structure/skinr/rules/'. $rule->rid . '/delete'),
    );
    $rows[] = $row;
  }

  $link = l(t('Create a new rule'), 'admin/structure/skinr/rules/add');
  $row = array();
  if (empty($rows)) {
    $row[] = array(
      'data' => t('No rules have been set up yet. !url.', array('!url' => $link)),
      'colspan' => 4,
    );
  }
  else {
    $row[] = array(
      'data' => t('!url.', array('!url' => $link)),
      'colspan' => 4,
    );
  }
  $rows[] = $row;

  $output .= theme('table', array('header' => $headers, 'rows' => $rows));
  $output .= drupal_render($form);

  return $output;
}

/**
 * Menu callback; displays the edit form for a skinr rule.
 *
 * @ingroup forms
 */
function skinr_rule_add($form, &$form_state) {
  $form = array();
  $form['#tree'] = TRUE;

  $form['rule']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => !empty($form_state['values']['rule']['title']) ? $form_state['values']['rule']['title'] : '',
    '#description' => t('Descriptive title for this rule; used by administrators.'),
    '#required' => TRUE,
  );
  $options = array('page' => t('Page'));
   foreach (list_themes() as $theme_name => $theme) {
     if (empty($theme->status)) {
       continue;
     }
     // Create a list options containing visible regions of this theme.
     $regions = array();
     foreach (system_region_list($theme_name, REGIONS_VISIBLE) as $region_name => $region) {
       $regions['region__' . $region_name] = $region;
     }
     // Group the list of options by theme.
     $key = t('@name Regions', array('@name' => $theme->info['name']));
     $options[$key] = $regions;
  }
  $form['rule']['rule_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => $options,
    '#default_value' => !empty($form_state['values']['rule']['rule_type']) ? $form_state['values']['rule']['rule_type'] : '',
    '#description' => t('Type of element the rule is applied to.'),
    '#required' => TRUE,
  );

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );

  return $form;
}

/**
 * Process skinr_rule_add() submissions.
 */
function skinr_rule_add_submit($form, &$form_state) {
  $rule = new stdClass();
  $rule->rid = NULL;
  $rule->title = $form_state['values']['rule']['title'];
  $rule->rule_type = $form_state['values']['rule']['rule_type'];
  $rule->node_types = array();
  $rule->roles = array();
  $rule->visibility = 0;
  $rule->pages = '';

  skinr_rule_save($rule);
  // Set rule id, if we inserted a new rule to allow others to know what rule they're working with.
  $form_state['values']['rule']['rid'] = $rule->rid;

  $form_state['redirect'] = 'admin/structure/skinr/rules/'. $rule->rid . '/edit';
}

/**
 * Form builder for the rule configuration form.
 *
 * @param $rid
 *   The rule ID.
 *
 * @see skinr_rule_edit_submit()
 * @ingroup forms
 */
function skinr_rule_edit($form, &$form_state, $rule) {
  $form['skinr']['module'] = array(
    '#type' => 'hidden',
    '#value' => 'rules',
  );
  $form['skinr']['element'] = array(
    '#type' => 'hidden',
    '#value' => $rule->rid,
  );

  $form['rule'] = array(
    '#weight' => -1,
  );

  $form['rule']['rid'] = array(
    '#type' => 'value',
    '#value' => $rule->rid,
  );

  $form['rule']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Rule title'),
    '#default_value' => $rule->title,
    '#description' => t('Descriptive title for this rule; used by administrators.'),
    '#required' => TRUE,
  );

  $form['rule']['rule_type'] = array(
    '#type' => 'hidden',
    '#value' => $rule->rule_type,
  );
  $form['rule']['rule_type_displayed'] = array(
    '#type' => 'item',
    '#title' => t('Rule type'),
    '#markup' => $rule->rule_type,
    '#description' => t('Type of element the rule is applied to.'),
  );

  // Visibility settings.
  $form['visibility_title'] = array(
    '#type' => 'item',
    '#title' => t('Visibility settings'),
  );
  $form['visibility'] = array(
    '#type' => 'vertical_tabs',
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'skinr_ui') . '/js/skinr_ui.rules.js'),
    ),
  );

  // Per-path visibility.
  $form['visibility']['path'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'visibility',
    '#weight' => 0,
  );

  $access = user_access('use PHP for settings');
  if ($rule->visibility == SKINR_RULE_VISIBILITY_PHP && !$access) {
    $form['visibility']['path']['visibility'] = array(
      '#type' => 'value',
      '#value' => SKINR_RULE_VISIBILITY_PHP,
    );
    $form['visibility']['path']['pages'] = array(
      '#type' => 'value',
      '#value' => $rule->pages,
    );
  }
  else {
    $options = array(
      SKINR_RULE_VISIBILITY_NOTLISTED => t('All pages except those listed'),
      SKINR_RULE_VISIBILITY_LISTED => t('Only the listed pages'),
    );
    $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));

    if (module_exists('php') && $access) {
      $options += array(SKINR_RULE_VISIBILITY_PHP => t('Pages on which this PHP code returns <code>TRUE</code> (experts only)'));
      $title = t('Pages or PHP code');
      $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
    else {
      $title = t('Pages');
    }
    $form['visibility']['path']['visibility'] = array(
      '#type' => 'radios',
      '#title' => t('Show block on specific pages'),
      '#options' => $options,
      '#default_value' => $rule->visibility,
    );
    $form['visibility']['path']['pages'] = array(
      '#type' => 'textarea',
      '#title' => '<span class="element-invisible">' . $title . '</span>',
      '#default_value' => $rule->pages,
      '#description' => $description,
    );
  }

  // Per-node visbility.
  $form['visibility']['node_type'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'visibility',
    '#weight' => 5,
  );
  $form['visibility']['node_type']['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show block for specific content types'),
    '#default_value' => $rule->node_types,
    '#options' => node_type_get_names(),
    '#description' => t('Show this block only on pages that display content of the given type(s). If you select no types, there will be no type-specific limitation.'),
  );

  // Per-role visibility.
  $role_options = array_map('check_plain', user_roles());
  $form['visibility']['role'] = array(
    '#type' => 'fieldset',
    '#title' => t('Roles'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'visibility',
    '#weight' => 10,
  );
  $form['visibility']['role']['roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show block for specific roles'),
    '#default_value' => $rule->roles,
    '#options' => $role_options,
    '#description' => t('Show this rule only for the selected role(s). If you select no roles, the rule will be visible to all users.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save rule'),
  );
  $form['actions']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#submit' => array('skinr_rule_delete_submit'),
  );

  return $form;
}

/**
 * Form submission handler for the rule configuration form.
 *
 * @see skinr_rule_edit()
 */
function skinr_rule_edit_submit($form, &$form_state) {
  $rule = new stdClass();
  $rule->rid = !empty($form_state['values']['rid']) ? $form_state['values']['rid'] : NULL;
  $rule->rule_type = $form_state['values']['rule_type'];
  $rule->title = $form_state['values']['title'];
  $rule->node_types = array_filter($form_state['values']['types']);
  $rule->roles = $form_state['values']['roles'];
  $rule->visibility = (int) $form_state['values']['visibility'];
  $rule->pages = trim($form_state['values']['pages']);

  skinr_rule_save($rule);
  // Set rule id, if we inserted a new rule to allow others to know what rule they're working with.
  $form_state['values']['rid'] = $rule->rid;

  $form_state['redirect'] = 'admin/structure/skinr/rules';
}

/**
 * Called from within the rule edit form; redirects to skinr_rule_delete_confirm().
 *
 * @ingroup forms
 */
function skinr_rule_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_REQUEST['destination'])) {
    $destination = drupal_get_destination();
    unset($_REQUEST['destination']);
  }
  $form_state['redirect'] = array('admin/structure/skinr/rules/' . $form_state['values']['rid'] . 'delete', $destination);
}

/**
 * Menu callback; displays the delete confirmation for a skinr rule.
 *
 * @param $rid
 *   The rule ID.
 *
 * @ingroup forms
 */
function skinr_rule_delete_confirm($form, &$form_state, $rule) {
  $form['rid'] = array(
    '#type' => 'value',
    '#value' => $rule->rid,
  );

  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $rule->title)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/structure/skinr/rules',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Process skinr_rule_delete_confirm() submissions.
 */
function skinr_rule_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    skinr_rule_delete($form_state['values']['rid']);
  }

  $form_state['redirect'] = 'admin/structure/skinr/rules';
}
