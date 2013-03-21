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
  return TRUE;
}

function yamlconfig_node_type_handler_create($def) {
  $translate = !empty($def['translatable']) ? !!$def['translatable'] : FALSE;
  node_type_save((object) $def);
  if ($translate) {
    // @todo we should remove this and force them to define it through var.
    variable_set('language_content_type_' . $def['type'], 4);
  }
}

function yamlconfig_node_type_handler_refresh($def) {
  yamlconfig_node_type_handler_create($def);
}

function yamlconfig_node_type_handler_disable($def) {
  $def += array(
    'disabled' => 1,
  );
  node_type_save((object) $def);
}

function yamlconfig_node_type_handler_uninstall($def) {
  node_type_delete($def['type']);
  variable_del('language_content_type_' . $def['type']);
}