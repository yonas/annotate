<?php
// $Id$

/**
 * Field handler to present a link node translate.
 */
class annotate_handler_field_note extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['format'] = 'note_format';
    $this->additional_fields['visibility'] = 'visibility';
  }

  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    $this->ensure_my_table();
    // Add the field.
    $this->field_alias = $this->query->add_field($this->table_alias, $this->real_field);
    $this->add_additional_fields();
    // Join the node table. Needed for the visibility WHERE query
    $join = new views_join();
    $join->construct('node', $this->table_alias, 'nid', 'nid');
    $join->type = 'INNER';
    $this->node_table = $this->query->ensure_table('note_node', $this->relationship, $join);

    $access = user_access( ANNOTATE_READ_PUBLISHED_ANNOTATION) ? '1' : '0';
    // Add where clause to query.
    $where = '((annotate.visibility = 3 AND annotate.nid IN (SELECT nid FROM annotate WHERE uid = ***CURRENT_USER***))
                OR (annotate.visibility = 1 AND note_node.uid=***CURRENT_USER***)
                OR (annotate.visibility = 2)
                OR (annotate.uid = ***CURRENT_USER***)
                OR  ***CURRENT_USER*** = 1)
                AND '. $access;
    $this->query->add_where($this->options['group'], $where, $values);
  }

  /**
   * Called to render this field.
   */
  function render($values) {
    // render the annotation note
    $value = $values->{$this->field_alias};
    $format = $values->{$this->aliases['note_format']};
    if ($value) {
      return check_markup($value, $format, FALSE);
    }
  }
}
