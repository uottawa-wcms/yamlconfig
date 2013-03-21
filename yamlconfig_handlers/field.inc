<?php

function yamlconfig_field_handler_validate($definition) {
  if (!isset($definition['field_name'])) {
    return FALSE;
  }
  if (!isset($definition['type'])) {
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_field_handler_create($definition) {
  $check = field_info_field($definition['field_name']);
  if (empty($check)) {
    field_create_field($definition);
  }
}

function yamlconfig_field_handler_refresh($definition) {
  field_update_field($definition);
}

function yamlconfig_field_handler_uninstall($definition) {
  field_delete_field($definition['field_name']);
}

function yamlconfig_field_handler_list() {
  $fields = array_keys(field_info_fields());
  $list = array();
  foreach ($fields as $field_name) {
    $list[$field_name] = $field_name;
  }
  return $list;
}

function yamlconfig_field_handler_export($key) {
  $info = field_info_field($key);
  unset($info['id']);
  unset($info['module']);
  unset($info['storage']);
  unset($info['deleted']);
  unset($info['columns']);
  return $info;
}