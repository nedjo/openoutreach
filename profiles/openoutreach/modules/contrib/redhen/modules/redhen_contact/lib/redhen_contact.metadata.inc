<?php

/**
 * Controls metadata for Redhen contacts
 *
 * Redhen utilizes custom property attributes to determine if a property
 * should be available as a filter on the listing page. These attributes are
 *   filter: TRUE to add as a filter.
 *   filter_operator: EFQ supported operators. Defaults to = or IN depending on value submitted
 *   field_type: textfield, select, etc.
 *   options list: callback that returns the options for this field.
 */
class RedhenContactMetadataController extends EntityDefaultMetadataController {

  /**
   * Overrides entityPropertyInfo().
   *
   * @return array
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['type'] = array(
      'label' => t('Type'),
      'description' => t('The type of the contact.'),
      'type' => 'token',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer redhen contacts',
      'options list' => 'redhen_contact_type_options_list',
      'required' => TRUE,
      'schema field' => 'type',
    );
    $properties['email'] = array(
      'label' => t("Default email"),
      'description' => t("The default email for this contact."),
      'type' => 'text',
      'getter callback' => 'redhen_contact_property_email_get',
      'setter callback' => 'redhen_contact_property_email_set',
      'computed' => TRUE,
      'entity views field' => TRUE,
      'filter' => TRUE,
    );
    $properties['created'] = array(
      'label' => t("Created"),
      'description' => t("The date the contact was created."),
      'type' => 'date',
      'schema field' => 'created',
      'setter callback' => 'entity_property_verbatim_set',
    );
    $properties['updated'] = array(
      'label' => t("Updated"),
      'description' => t("The date the contact was updated."),
      'type' => 'date',
      'schema field' => 'updated',
      'setter callback' => 'entity_property_verbatim_set',
    );
    $properties['first_name'] = array_merge($properties['first_name'], array(
      'label' => t('First name'),
      'filter' => TRUE,
      'required' => TRUE,
      'field_type' => 'textfield',
      'setter callback' => 'entity_property_verbatim_set',
      'filter_operator' => 'CONTAINS',
    ));
    $properties['middle_name'] = array_merge($properties['middle_name'], array(
      'label' => t('Middle Name'),
      'filter' => TRUE,
      'field_type' => 'textfield',
      'setter callback' => 'entity_property_verbatim_set',
      'filter_operator' => 'CONTAINS',
    ));
    $properties['last_name'] = array_merge($properties['last_name'], array(
      'label' => t('Last name'),
      'required' => TRUE,
      'filter' => TRUE,
      'field_type' => 'textfield',
      'setter callback' => 'entity_property_verbatim_set',
      'filter_operator' => 'CONTAINS',
    ));
    $properties['full_name'] = array(
      'label' => t('Full name'),
      'description' => t('The full name of the contact.'),
      'filter' => TRUE,
      'type' => 'text',
      'getter callback' => 'redhen_contact_property_full_name_get',
      'computed' => TRUE,
      'entity views field' => TRUE,
      'filter_operator' => 'CONTAINS',
    );
    $properties['redhen_state'] = array_merge($properties['redhen_state'], array(
      'label' => t('State'),
      'filter' => TRUE,
      'field_type' => 'select',
      'options list' => 'redhen_state_options',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
    ));

    // Entities.
    $properties['user'] = array(
      'label' => t("User"),
      'type' => 'user',
      'description' => t("The Drupal user associated with the contact."),
      'getter callback' => 'redhen_contact_property_user_get',
      'setter callback' => 'redhen_contact_property_user_set',
    );
    $properties['author'] = array(
      'label' => t("Author"),
      'type' => 'user',
      'description' => t("The author of the contact record."),
      'schema field' => 'author_uid',
    );

    return $info;
  }

}
