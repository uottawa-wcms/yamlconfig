<?php

function yamlconfig_field_instance_handler_validate($def) {
  if (!isset($def['field_name'])) {
    return FALSE;
  }
  if (!isset($def['entity_type'])) {
    return FALSE;
  }
  if (!isset($def['bundle'])) {
    return FALSE;
  }
  $info = entity_get_info($def['entity_type']);
  if (empty($info)) {
    return FALSE;
  }
  if (!in_array($def['bundle'], $info['bundles'])) {
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_field_instance_handler_preprocess(&$def) {
  if (!empty($def['widget'])) {
    yamlconfig_stored_value_replacement('widget_instance', $def['widget']);
  }
  if (!empty($def['settings']['better_formats'])) {
    yamlconfig_stored_value_replacement('wysiwyg_instance', $def['settings']['better_formats']);
  }
}

function yamlconfig_field_instance_handler_create($def) {
  if (!field_info_instance($def['entity_type'], $def['field_name'], $def['bundle'])) {
    field_create_instance($def);
  }
}

function yamlconfig_field_instance_handler_refresh($def) {
  field_update_instance($def);
}

function yamlconfig_field_instance_handler_uninstall($def) {
  field_delete_instance($def);
}