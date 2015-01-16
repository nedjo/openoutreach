<?php

/**
 * @file
 * Rules integration for RedHen Contacts.
 */

/**
 * Implements hook_rules_action_info().
 */
function redhen_contact_rules_action_info() {
  $actions = array();

  // Declare some defaults for all actions.
  $defaults = array(
    'group' => t('Redhen Contact'),
    'access callback' => 'redhen_contact_access',
  );

  // Add an action to load contact by email address.
  $actions['redhen_contact_fetch_by_mail'] = $defaults + array(
    'label' => t('Fetch contact by email'),
    'base' => 'redhen_contact_rules_action_fetch_by_mail',
    'provides' => array(
      'fetched_contact' => array('type' => 'redhen_contact', 'label' => t('Fetched contact')),
    ),
  );
  $actions['redhen_contact_fetch_by_mail']['parameter']['mail'] = array(
    'type' => 'text',
    'label' => t('Email address'),
    'description' => t('The email address to fetch by.'),
  );

  return $actions;
}

/**
 * Implements hook_rules_condition_info().
 */
function redhen_contact_rules_condition_info() {
  $conditions = array();

  $conditions['redhen_contact_exists_by_email'] = array(
    'label' => t('Contact exists by email'),
    'base' => 'redhen_contact_rules_condition_exists_by_email',
    'group' => t('Redhen Contact'),
    'parameter' => array(
      'mail' => array(
        'type' => 'text',
        'label' => t('Email address'),
        'description' => t('The email address to check by.'),
      ),
    ),
  );

  return $conditions;
}

/**
 * Rules action: fetch contact by email address.
 */
function redhen_contact_rules_action_fetch_by_mail($mail) {
  $contacts = redhen_contact_load_by_mail($mail);
  $contact = $contacts ? array_shift($contacts) : NULL;
  return array('fetched_contact' => $contact);
}

/**
 * Rules condition: contact exists by email address.
 */
function redhen_contact_rules_condition_exists_by_email($mail) {
  $contacts = redhen_contact_load_by_mail($mail);
  return is_array($contacts);
}