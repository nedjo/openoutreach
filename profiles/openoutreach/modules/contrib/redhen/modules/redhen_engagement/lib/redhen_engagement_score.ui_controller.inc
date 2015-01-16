<?php

/**
 * UI Controller for Redhen engagement scores. Adds the score column.
 */
class RedhenEngagementScoreUIController extends EntityDefaultUIController {

  /**
   * Override parent to set the score header.
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    $additional_header[] = t('Score');
    return parent::overviewTableHeaders($conditions, $rows, $additional_header);
  }

  /**
   * Override parent to set the score column.
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $additional_cols[] = $entity->score;
    return parent::overviewTableRow($conditions, $id, $entity, $additional_cols);
  }

}
