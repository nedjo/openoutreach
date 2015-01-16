<?php

/**
 * RedhenMembership Views Controller class.
 */
class RedhenEngagementViewsController extends EntityDefaultViewsController {

  /**
   * Add extra fields to views_data().
   */
  public function views_data() {
    $data = parent::views_data();

    $entity_info = entity_get_info();

    foreach ($entity_info as $entity_type => $info) {
      if ($entity_type == 'redhen_note') {
        // Entity to Engagement.
        $data[$info['base table']]['redhen_engagement_rel'] = array(
          'group' => t('Engagement'),
          'title' => t('@entity to Engagement',
            array('@entity' => drupal_ucfirst($info['label']))),
          'help' => t('The Note associated with the @entity entity.',
            array('@entity' => drupal_ucfirst($info['label']))),
          'relationship' => array(
            'entity' => $entity_type,
            'handler' => 'redhen_membership_handler_relationship',
            'label' => t('@entity being the Note',
              array('@entity' => $entity_type)),
            'base' => 'redhen_engagement',
            'base field' => 'entity_id',
            'relationship field' => $info['entity keys']['id'],
          ),
        );

        // Engagement to entity.
        $data['redhen_engagement']['redhen_engagement_related_' . $entity_type] = array(
          'group' => t('Engagement'),
          'title' => t('Engagement to @entity',
            array('@entity' => drupal_ucfirst($info['label']))),
          'help' => t('The @entity entity that is associated with the Engagement.',
            array('@entity' => $info['label'])),
          'relationship' => array(
            'handler' => 'views_handler_relationship',
            'label' => t('@entity from Note',
              array('@entity' => $entity_type)),
            'base' => $info['base table'],
            'base field' => $info['entity keys']['id'],
            'relationship field' => 'entity_id',
          ),
        );
      }
    }

    return $data;
  }
}

/**
 * RedhenMembership Views Controller class.
 */
class RedhenEngagementScoreViewsController extends EntityDefaultViewsController {

  /**
   * Add extra fields to views_data().
   */
  public function views_data() {
    $data = parent::views_data();

    $entity_info = entity_get_info();

    foreach ($entity_info as $entity_type => $info) {
      if ($entity_type == 'redhen_engagement') {
        // Entity to engagment_score.
        $data[$info['base table']]['redhen_engagement_score_rel'] = array(
          'group' => t('Engagement Score'),
          'title' => t('@entity to Engagement Score',
            array('@entity' => drupal_ucfirst($info['label']))),
          'help' => t('The Note associated with the @entity entity.',
            array('@entity' => drupal_ucfirst($info['label']))),
          'relationship' => array(
            'entity' => $entity_type,
            'label' => t('@entity being the Engagement',
              array('@entity' => $entity_type)),
            'base' => 'redhen_engagement_score',
            'base field' => 'name',
            'relationship field' => 'engagement_score',
          ),
        );

        // Engagement score to entity.
        $data['redhen_engagement_score']['redhen_engagement_related_' . $entity_type] = array(
          'group' => t('Engagement Score'),
          'title' => t('Engagement Score to @entity',
            array('@entity' => drupal_ucfirst($info['label']))),
          'help' => t('The @entity entity that is associated with the Engagement.',
            array('@entity' => $info['label'])),
          'relationship' => array(
            'handler' => 'views_handler_relationship',
            'label' => t('@entity from Redhen Engagement',
              array('@entity' => $entity_type)),
            'base' => $info['base table'],
            'base field' => 'engagement_score_id',
            'relationship field' => 'engagement_score_id',
          ),
        );
      }
    }

    return $data;
  }
}

