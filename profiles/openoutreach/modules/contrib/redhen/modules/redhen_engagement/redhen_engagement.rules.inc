<?php

/**
 * @file
 * Rules integration for RedHen Engagements.
 */

/**
 * Implements hook_rules_action_info().
 */
function redhen_engagement_rules_action_info() {
  $actions = array();

  // Declare some defaults for all actions.
  $defaults = array(
    'parameter' => array(
      'scores' => array(
        'type' => 'list<token>',
        'label' => t('Engagement Scores'),
        'description' => t('One or more scores that will be used for this engagement.'),
        'options list' => 'redhen_engagement_score_options',
      ),
    ),
    'group' => t('Engagement'),
    'access callback' => 'redhen_engagement_access',
  );
  // Declare parameters used by both email and user ID actions.
  $parameters = array(
    'entity' => array(
      'type' => 'entity',
      'label' => t('Entity'),
      'description' => t('Specifies the entity that a score should be registered for.'),
    ),
  );

  // Add an action to score an engagement by email address.
  $actions['score_engagement_by_mail'] = $defaults + array(
    'label' => t('Score engagement by email'),
    'base' => 'redhen_engagement_rules_action_score_by_mail',
  );
  $actions['score_engagement_by_mail']['parameter'] += $parameters;
  $actions['score_engagement_by_mail']['parameter']['mail'] = array(
    'type' => 'text',
    'label' => t('Email address'),
    'description' => t('The email address to score an engagement by.'),
  );

  // Add an action to score an engagement by user ID.
  $actions['score_engagement_by_uid'] = $defaults + array(
    'label' => t('Score engagement by user ID'),
    'base' => 'redhen_engagement_rules_action_score_by_uid',
  );
  $actions['score_engagement_by_uid']['parameter'] += $parameters;
  $actions['score_engagement_by_uid']['parameter']['uid'] = array(
    'type' => 'integer',
    'label' => t('User ID'),
    'description' => t('The user ID to score an engagement by.'),
  );

  // webform
  if (module_exists('webform_rules')) {
    $actions['score_webform_engagement'] = $defaults + array(
       'label' => t('Score webform engagement'),
       'base' => 'redhen_engagement_rules_action_score_webform',
    );
    $actions['score_webform_engagement']['parameter']['webform'] = array(
      'type' => 'webform',
      'label' => t('Webform'),
      'description' => t('The webform submission to be scored. <em>Note: At this time scoring of anonymous webform submissions is not supported.</em>'),
    );
  }

  return $actions;
}

/**
 * Rules action: score an engagement by user ID.
 */
function redhen_engagement_rules_action_score_by_uid($scores, $entity, $uid) {
  if ($contact = redhen_contact_load_by_user(user_load($uid))) {
    redhen_engagement_rules_action_score_contact($scores, $contact, t('Scored @label', array('@label' => $entity->label())), $entity->type(), $entity->getIdentifier());
  }
}

/**
 * Rules action: score an engagement by email address.
 */
function redhen_engagement_rules_action_score_by_mail($scores, $entity, $mail) {
  if ($contacts = redhen_contact_load_by_mail($mail)) {
    foreach ($contacts as $contact) {
      redhen_engagement_rules_action_score_contact($scores, $contact, t('Scored @label', array('@label' => $entity->label())), $entity->type(), $entity->getIdentifier());
    }
  }
}

/**
 * Helper function for when the "webform engagement" Rule action is triggered.
 */
function redhen_engagement_rules_action_score_webform($scores, $webform) {
  $result = db_query('SELECT w.nid, w.uid FROM {webform_submissions} w WHERE w.sid = :sid', array(':sid' => $webform['sid']));
  foreach ($result as $record) {
    if ($record->uid != 0) {
      $contact = redhen_contact_load_by_user(user_load($record->uid));
      $nid = $record->nid;
    }
  }

  if ($contact) {
    redhen_engagement_rules_action_score_contact($scores, $contact, t('Scored webform submission'), 'node', $nid);
  }
}

/**
 * Helper function for saving a comment engagement score when the Rule action is triggered.
 */
function redhen_engagement_rules_action_score_contact($score_ids, $contact, $description = '', $entity_type, $entity_id) {
  foreach ($score_ids as $id) {
    $score = entity_load_single('redhen_engagement_score', $id);
    $engagement = redhen_engagement_create($score->name, $contact->contact_id, $description, $entity_type, $entity_id);
    redhen_engagement_save($engagement);
  }
}
