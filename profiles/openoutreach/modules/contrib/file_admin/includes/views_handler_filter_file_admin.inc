<?php
/**
 * Filter by published status
 */
class views_handler_filter_file_admin extends views_handler_filter {
  function admin_summary() { }
  function operator_form(&$form, &$form_state) { }
  function can_expose() { return FALSE; }

  function query() {
    $table = $this->ensure_my_table();
    $this->query->add_where_expression($this->options['group'], "$table.published = 1 OR ($table.uid = ***CURRENT_USER*** AND ***CURRENT_USER*** <> 0 AND ***VIEW_OWN_UNPUBLISHED_FILES*** = 1) OR ***BYPASS_FILE_ACCESS*** = 1");
  }
}
