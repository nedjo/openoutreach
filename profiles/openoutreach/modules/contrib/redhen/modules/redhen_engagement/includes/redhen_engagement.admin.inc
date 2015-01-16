<?php

/**
 * @file
 * Redhen enagagement score editing UI.
 */

/**
 * Generates the Redhen Contact type editing form.
 */
function redhen_engagement_score_form($form, &$form_state, $redhen_engagement_score, $op = 'edit') {
  if ($op == 'clone') {
    $redhen_engagement_score->label .= ' (cloned)';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $redhen_engagement_score->label,
    '#description' => t('The human-readable name of this engagement score.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $redhen_engagement_score->name,
    '#maxlength' => 32,
    '#disabled' => $redhen_engagement_score->locked && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'redhen_engagement_get_scores',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this engagement score. It must only contain lowercase letters, numbers, and underscores.'),
  );
  $form['score'] = array(
    '#title' => t('Score'),
    '#type' => 'textfield',
    '#default_value' => $redhen_engagement_score->score,
    '#description' => t('The numeric value of this score.'),
    '#required' => TRUE,
    '#size' => 10,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Engagement Score'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function redhen_engagement_score_form_submit(&$form, &$form_state) {
  $redhen_engagement_score = entity_ui_form_submit_build_entity($form, $form_state);
  $redhen_engagement_score->save();
  $form_state['redirect'] = 'admin/structure/redhen/engagement_scores';
}

