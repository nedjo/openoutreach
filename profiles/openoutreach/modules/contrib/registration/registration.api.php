<?php
/**
 * @file
 * API documentation for Relation module.
 */

/**
 * Override registration_access with custom access control logic.
 *
 * @param $op
 * @param Registration $registration
 * @param object $account
 *
 * @return bool
 */
function hook_registration_access($op, $registration, $account = NULL) {
  if ($registration->user_uid == $account->uid) {
    return TRUE;
  }
}

/**
 * Provide a form API element exposed as a Registration entity setting.
 *
 * @param array $settings
 *   Existing settings values.
 *
 * @return array
 *   A FAPI array for a registration setting.
 */
function hook_registration_entity_settings($settings) {
  return array(
    'registration_entity_access_roles' => array(
      '#type' => 'checkboxes',
      '#title' => t('Roles'),
      '#description' => t('Override default access control settings by selecting which roles can register for this event.'),
      '#options' => user_roles(),
      '#default_value' => isset($settings['settings']['registration_entity_access_roles']) ? $settings['settings']['registration_entity_access_roles'] : NULL,
    ),
  );
}

/**
 * Allow modules to override event count.
 *
 * This can impact access control and the ability for users to register.
 *
 * @param int $count
 *
 * @param array $context
 *   array(
 *     'entity_type' => $entity_type,
 *     'entity_id' => $entity_id,
 *     'registration_id' => $registration_id,
 *     'settings' => $settings,
 *   );
 */
function hook_registration_even_count_alter($count, $context) {

}
