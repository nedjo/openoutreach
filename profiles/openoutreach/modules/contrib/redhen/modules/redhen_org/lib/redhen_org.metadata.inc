<?php

/**
 * Controls metadata for Redhen organizations
 *
 * Redhen utilizes custom property attributes to determine if a property
 * should be available as a filter on the listing page. These attributes are
 *   filter: TRUE to add as a filter.
 *   filter_operator: EFQ supported operators. Defaults to = or IN depending on value submitted
 *   field_type: textfield, select, etc.
 *   options list: callback that returns the options for this field.
 */
class RedhenOrgMetadataController extends EntityDefaultMetadataController {

  /**
   * Overrides entityPropertyInfo().
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['type'] = array(
      'label' => t('Type'),
      'description' => t('The type of organization.'),
      'type' => 'token',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer redhen orgs',
      'options list' => 'redhen_org_type_options_list',
      'required' => TRUE,
      'schema field' => 'type',
    );
    $properties['label'] = array(
      'label' => t('Organization Name'),
      'filter' => TRUE,
      'field_type' => 'textfield',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'filter_operator' => 'CONTAINS',
    ) + $properties['label'];
    $properties['created'] = array(
      'label' => t("Created"),
      'description' => t("The date the organization was created."),
      'type' => 'date',
      'schema field' => 'created',
      'setter callback' => 'entity_property_verbatim_set',
    );
    $properties['updated'] = array(
      'label' => t("Updated"),
      'description' => t("The date the organization was updated."),
      'type' => 'date',
      'schema field' => 'updated',
      'setter callback' => 'entity_property_verbatim_set',
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
    $properties['primary_contact'] = array(
      'label' => t("Primary contact"),
      'type' => 'redhen_contact',
      'description' => t("The primary contact for the organization."),
      'schema field' => 'primary_contact_id',
    );
    $properties['author'] = array(
      'label' => t("Author"),
      'type' => 'user',
      'description' => t("The author of the organization record."),
      'schema field' => 'author_uid',
      'required' => TRUE,
    );

    return $info;
  }

}
