<?php
/**
 * @file
 * Provide active membership types as a field on contacts/organizations.
 */
class redhen_membership_handler_field_active_member_type extends views_handler_field_prerender_list {

  function query() {
    $this->ensure_my_table();

    if ($this->table == 'redhen_org') {
      $id_field = 'org_id';
    }
    if ($this->table == 'redhen_contact') {
      $id_field = 'contact_id';
    }
    $this->field_alias = $this->query->add_field(NULL, $id_field);

    $this->add_additional_fields();
  }

  function pre_render(&$values) {

    $membership_types = redhen_membership_get_types();

    foreach ($values as $value) {
      $entity_id = $this->get_value($value, NULL, TRUE);
      $memberships = redhen_membership_query(array(
        'entity_type' => $this->table,
        'entity_id' => $entity_id,
        'membership_state' => REDHEN_MEMBERSHIP_ACTIVE
      ));

      if ($memberships) {
        foreach ($memberships as $membership) {
          $this->items[$entity_id][$membership->type]['membership_type_label'] = $membership_types[$membership->type]->label;
        }
      }
    }
  }

  function render_item($count, $item) {
    return $item['membership_type_label'];
  }

}
