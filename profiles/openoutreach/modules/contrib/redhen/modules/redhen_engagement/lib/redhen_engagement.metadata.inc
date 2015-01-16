<?php

/**
 * Controls metadata for Redhen Engagement Scores.
 *
 * Redhen utilizes custom property attributes to determine if a property
 * should be available as a filter on the listing page. These attributes are
 *   filter: TRUE to add as a filter.
 *   filter_operator: EFQ supported operators. Defaults to = or IN depending on value submitted
 *   field_type: textfield, select, etc.
 *   options list: callback that returns the options for this field.
 */
class RedhenEngagementMetadataController extends EntityDefaultMetadataController {

  /**
   * Override parent to define entity propery metadat for engagements.
   *
   * @return array
   *   Associative array of entity properties.
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['created'] = array(
      'label' => t("Created"),
      'description' => t("The date the note was created."),
      'type' => 'date',
      'schema field' => 'created',
      // RedHen specific attributes.
      'filter' => TRUE,
      'field_type' => 'textfield',
    );
    // Entities.
    $properties['entity'] = array(
      'label' => t("Source entity"),
      'type' => 'entity',
      'description' => t("The host entity."),
      'getter callback' => 'redhen_engagement_property_source_get',
      'setter callback' => 'entity_property_verbatim_set',
    );
    $properties['contact'] = array(
      'label' => t("Contact"),
      'type' => 'redhen_contact',
      'description' => t("The redhen_contact this engagement applies to."),
      'schema field' => 'contact_id',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
    );
    $properties['author'] = array(
      'label' => t("Author"),
      'type' => 'user',
      'description' => t("The author of the note."),
      'schema field' => 'author_uid',
      'required' => TRUE,
    );
    $properties['engagement_score'] = array(
      'label' => t('Engagement score'),
      'type' => 'redhen_engagement_score',
      'schema field' => 'engagement_score',
      'description' => t('The engagement score.'),
      'options list' => 'redhen_engagement_score_options',
      'setter callback' => 'entity_property_verbatim_set',
      // RedHen specific attributes.
      'field_type' => 'select',
      'filter' => TRUE,
      'required' => TRUE,
    );

    return $info;
  }

}
