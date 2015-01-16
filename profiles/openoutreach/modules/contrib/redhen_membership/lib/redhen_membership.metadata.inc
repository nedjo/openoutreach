<?php

/**
 * Controls metadata for Redhen memberships
 *
 * Redhen utilizes custom property attributes to determine if a property
 * should be available as a filter on the listing page. These attributes are
 *   filter: TRUE to add as a filter.
 *   field_type: textfield, select, etc.
 *   options: array of options for select field types.

 */
class RedhenMembershipMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];


    $properties['membership_id'] = array(
      'label' => t("Membership ID"),
      'type' => 'integer',
      'description' => t("The unique ID of the membership."),
      'schema field' => 'membership_id',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['entity_type'] = array(
      'label' => t("Host entity type"),
      'type' => 'token',
      'description' => t("The entity type of the host entity."),
      'required' => TRUE,
      'schema field' => 'entity_type',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['entity_id'] = array(
      'label' => t("Host entity ID"),
      'type' => 'integer',
      'description' => t("The entity ID of the host entity."),
      'required' => TRUE,
      'schema field' => 'entity_id',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['start_date'] = array(
      'label' => t("Start Date"),
      'description' => t("The date the membership begins."),
      'type' => 'date',
      'field_type' => 'textfield',
      'schema field' => 'start_date',
      'filter' => TRUE,
      'setter callback' => 'entity_property_verbatim_set',
    );
    $properties['expire_date'] = array(
      'label' => t("Expiration Date"),
      'description' => t("The date the membership expires."),
      'type' => 'date',
      'field_type' => 'textfield',
      'schema field' => 'expire_date',
      'filter' => TRUE,
      'setter callback' => 'entity_property_verbatim_set',
    );
    $properties['created'] = array(
      'label' => t("Created"),
      'description' => t("The date the membership was created."),
      'type' => 'date',
      'schema field' => 'created',
      'setter callback' => 'entity_property_verbatim_set',
    );
    $properties['updated'] = array(
      'label' => t("Updated"),
      'description' => t("The date the membership was updated."),
      'type' => 'date',
      'schema field' => 'updated',
      'setter callback' => 'entity_property_verbatim_set',
    );
    $properties['membership_state'] = array(
      'label' => t('State'),
      'filter' => TRUE,
      'type' => 'integer',
      'field_type' => 'list',
      'required' => TRUE,
      'schema field' => 'membership_state',
      'setter callback' => 'entity_property_verbatim_set',
      'options list' => 'redhen_membership_state_options',
    );

    // Entities
    $properties['author'] = array(
      'label' => t("Author entity"),
      'type' => 'user',
      'description' => t("The author of the membership record."),
      'schema field' => 'author_uid',
    );

    $properties['entity'] = array(
      'label' => t("Host entity"),
      'type' => 'entity',
      'schema field' => 'entity',
      'description' => t("The host entity."),
      'getter callback' => 'redhen_membership_property_host_get',
    );

    return $info;
  }
}
