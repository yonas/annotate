<?php
// $Id $

/**
 * @file
 * Annotate Views support. Declares all the main tables to Views
 * @author Frans Kuipers http://drupal.org/user/103267
 **/

/**
 * hook_views_data()
 */
function annotate_views_data() {
  $tables['annotate'] = array(
    'table' => array(
      'group' => t('Annotations'),
      'join' => array(
        'users' => array(
          'table' => 'annotate',
          'left_field' => 'uid',
          'field' => 'uid'
         ),
         'node' => array(
           'table' => 'annotate',
           'left_field' => 'nid',
           'field' => 'nid'
         ),
       ),
      'base' => array(
        'field' => 'note',
        'title' => t('Annotation'),
        'help' => t('Notes added as annotations to node content.'),
      ),
    ),
    // Fields definitions
    'note' => array(
      'title' => t('Note'),
      'help' => t('The note text for this node'),
      // Information for displaying the note
      'field' => array(
        'handler' => 'annotate_handler_field_note',
        'format' => 'note_format',
      ),
      'extra' => array(
        array('field' => 'uid', 'value' => '***CURRENT_USER***', 'numeric' => TRUE),
      ),

    ),
    'timestamp' => array(
      'title' => t('Post date'),
      'help' => t('Date and time of when the comment was posted.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
    'visibility' => array(
      'title' => t('Visibility'),
      'help' => t('Visibility of the note, 0=private, 1=editor, 2=other, 3=collaborators.'),
      'field' => array(
        'handler' => 'annotate_handler_field_visibility',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_in_operator',
        'options callback' => '_annotate_get_visibility_list',
      ),
    ),
    'nid' => array(
      'title' => t('Node'),
      'help' => t('The node the note is annotated to.'),
      'relationship' => array(
        'base' => 'node',
        'base field' => 'nid',
        'handler' => 'views_handler_relationship',
        'label' => t('Node'),
      ),
    ),
    'uid' => array(
      'title' => t('User'),
      'help' => t("The User ID of the note's author."),
      'relationship' => array(
        'base' => 'users',
        'base field' => 'uid',
        'handler' => 'views_handler_relationship',
        'label' => t('User'),
      ),
    ),
    // uid alias to filter on current user
    'uid_current' => array(
      'real field' => 'uid',
      'title' => t('Current'),
      'help' => t('Filter the view to the currently logged in user.'),
      'filter' => array(
        'handler' => 'views_handler_filter_user_current',
        'type' => 'yes-no',
      ),
    ),
  );

  return $tables;
}

/**
 *  Implementation of hook_views_handlers().
 */
function annotate_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'annotate') . '/views',
    ),
    'handlers' => array(
      // field handler
      'annotate_handler_field_note' => array(
        'parent' => 'views_handler_field'
      ),
      'annotate_handler_field_visibility' => array(
        'parent' => 'views_handler_field'
      ),
      
    ),
  );
}
