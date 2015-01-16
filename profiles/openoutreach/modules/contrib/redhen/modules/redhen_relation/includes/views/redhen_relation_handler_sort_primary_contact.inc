<?php
/**
 * @file
 * Field that indicates of a specific contact is the primary contact for an organization
 */
class redhen_relation_handler_sort_primary_contact extends views_handler_sort {

  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();

    // @todo Make the ensure_tables work so we are explicit about the relationships that give us the contact_id/primary_contact_id
    $contact_table = $this->query->ensure_table('redhen_contact');
    $org_table = $this->query->ensure_table('redhen_org', $this->relationship);
    $comparison = 'primary_contact_id = ' . $contact_table . '.contact_id';
    $this->field_alias = $this->query->add_field(NULL, $comparison, 'is_primary');

    $this->query->add_orderby(NULL, NULL, $this->options['order'], $this->field_alias);
  }

}
