<?php

function yamlconfig_node_type_handler_preprocess(&$def) {
  $def += array(
    'base' => 'node_content',
    'title_label' => 'Title',
    'custom' => TRUE,
    'locked' => TRUE,
  );
}

function yamlconfig_node_type_handler_validate($def) {
  if (empty($def['type'])) {
    return FALSE;
  }
  if (empty($def['name'])) {
    return FALSE;
  }
  
}

function yamlconfig_node_type_handler_create($def) {
  node_type_save((object) $def);
  // do something with this
  //variable_set('language_content_type_uottawa_index_page',TRANSLATION_ENABLED);
}

function yamlconfig_node_type_handler_refresh($def) {
  node_type_save((object) $def);
}

function yamlconfig_node_type_handler_disable($def) {
  $def += array(
    'disabled' => 1,
  );
  node_type_save((object) $def);
}

function yamlconfig_node_type_handler_uninstall($def) {
  node_type_delete($def['type']);
}