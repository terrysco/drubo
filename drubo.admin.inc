<?php

/**
 * @file
 * Drubo configuration file
 */
function drubo_admin_form() {
  $form['drubo_profile_num'] = array(
    '#title' => t('Tweets'),
    '#description' => t(''),
    '#type' => 'textfield',
    '#size' => 5,
    '#required' => TRUE,
    '#default_value' => variable_get('drubo_profile_num', 3),
  );
  // Get an array of node types with internal names as keys and
  // "friendly names" as values. E.g.,
  // array('page' => 'Page', 'story' => 'Story')
  $options = node_get_types('names');
  $form['content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Types'),
  );
  $form['content']['drubo_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Users may post tweets on these content types'),
    '#options' => $options,
    '#default_value' => variable_get('drubo_node_types', array('page')),
    '#description' => t('A checkbox field will be available on these content types to post tweets.'),
  );
  return system_settings_form($form);
} 

