<?php
// $Id$

/**
 * Field handler to present a link node translate.
 */
class annotate_handler_field_visibility extends views_handler_field {
  /**
   * Called to render this field.
   */
  function render($values) {
  	$options = _annotate_get_visibility_list();
    return $options[$values->annotate_visibility];
  }
}
