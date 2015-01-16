<?php

/**
 * RedhenContact Views Controller class.
 */
class RedhenContactViewsController extends EntityDefaultViewsController {

  /**
   * Add extra fields to views_data().
   */
  public function views_data() {
    $data = parent::views_data();

    // Base table definition for redhen_contact_user so we can use it for joins.
    $data['redhen_contact_user']['table']['group'] = t('User');

    $data['redhen_contact_user']['table']['join'] = array(
      'redhen_contact' => array(
        'left_field' => 'contact_id',
        'field' => 'contact_id',
        // Only join where the linkage is active.
        'extra' => array(
          array('field' => 'status', 'value' => '1', 'operator' => '='),
        ),
      ),
      'users' => array(
        'left_field' => 'uid',
        'field' => 'uid',
        // Only join where the linkage is active.
        'extra' => array(
          array('field' => 'status', 'value' => '1', 'operator' => '='),
        ),
      ),
    );

    $data['redhen_contact_user']['uid'] = array(
      'group' => t('User'),
      'title' => t('Contact User UID'),
      'help' => t('The user id associated with this contact via redhen_contact_user'),
      'relationship' => array(
        'base' => 'users',
        'base field' => 'uid',
        'handler' => 'views_handler_relationship',
        'label' => t('User'),
        'title' => t('Contact User'),
        'help' => t('The user associated with this contact via redhen_contact_user'),
      ),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );

    $data['redhen_contact_user']['contact_id'] = array(
      'group' => t('Contact'),
      'title' => t('User Contact ID'),
      'help' => t('The contact id associated with this user via redhen_contact_user'),
      'relationship' => array(
        'base' => 'redhen_contact',
        'base field' => 'contact_id',
        'handler' => 'views_handler_relationship',
        'label' => t('Contact'),
        'title' => t('User Contact'),
        'help' => t('The contact associated with this user via redhen_contact_user'),
      ),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );

    return $data;
  }
}
