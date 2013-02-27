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
  var_dump('calling create handler');
  if (!field_info_field($definition['field_name'])) {
    field_create_field($definition);
  }
}

function yamlconfig_field_handler_refresh($definition) {
  field_update_field($definition);
}

function yamlconfig_field_handler_uninstall($definition) {
  field_delete_field($definition['field_name']);
}