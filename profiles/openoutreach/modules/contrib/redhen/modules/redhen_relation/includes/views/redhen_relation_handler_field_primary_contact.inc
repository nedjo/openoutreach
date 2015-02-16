<?php
/**
 * @file
 * Field that indicates of a specific contact is the primary contact for an organization
 */
class redhen_relation_handler_field_primary_contact extends views_handler_field_boolean {

  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();
    $contact_table = $this->ensure_table('redhen_contact');
    $org_table = $this->ensure_table('redhen_org', $this->relationship);
    $comparison = $org_table . '.primary_contact_id = ' . $contact_table . '.contact_id';
    $this->field_alias = $this->query->add_field(NULL, $comparison, 'is_primary');

    $this->add_additional_fields();
  }

  /**
   * Called to add the correct field alias in the query for this field.
   */
  function ensure_table($table, $relationship = NULL, $join = NULL) {
    // Check if the normal ensure_table works...
    if ($alias = $this->query->ensure_table($table, $relationship, $join)) {
      return $alias;
    }

    // Dig into what's available and pick a likely looking alias.
    foreach ($this->query->relationships as $alias => $info) {
      if ($relationship == $info['link']) {
        return $alias;
      }
    }

    // If we get to here, whatever. We don't check the return value anyway.
    return FALSE;
  }
}
