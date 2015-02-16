<?php
/**
 * @file
 * EntityReference extensions for Redhen Contacts.
 */

/**
 * RedHenContact selection handler.
 */
class EntityReference_SelectionHandler_Generic_redhen_contact extends EntityReference_SelectionHandler_Generic {
  /**
   * Build an EntityFieldQuery to get referencable entities.
   */
  protected function buildEntityFieldQuery($match = NULL, $match_operator = 'CONTAINS') {
    // @todo Enable filtering by first OR last name. This will require adding
    // metadata and/or tags to the query, altering it using a
    // hook_query_TAG_alter(), and using a db_or() to generate the OR condition.
    // See http://drupal.stackexchange.com/questions/14499/using-or-with-entityfieldquery
    // and https://api.drupal.org/api/drupal/includes!database!database.inc/function/db_or/7
    // and http://www.phase2technology.com/blog/or-queries-with-entityfieldquery/.
    // For now, the filter is just on first name.
    $query = parent::buildEntityFieldQuery($match, $match_operator);

    $query->propertyCondition('first_name', $match, $match_operator);

    return $query;
  }

}
