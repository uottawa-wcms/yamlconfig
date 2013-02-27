<?php

function yamlconfig_field_replace_handler_validate($def) {
  if (!module_exists('title')) {
    return FALSE;
  }
  if (empty($def['entity_type'])) {
    return FALSE;
  }
  if (empty($def['bundle'])) {
    return FALSE;
  }
  if (empty($def['field'])) {
    return FALSE;
  }
}

function yamlconfig_field_replace_handler_create($def) {
  title_field_replacement_toggle($def['entity_type'], $def['bundle'], $def['field']);
}

function yamlconfig_field_replace_handler_refresh($def) {
  if (!title_field_replacement_enabled($def['entity_type'], $def['bundle'], $def['field'])) {
    yamlconfig_field_replace_handler_create($def);
  }
}

function yamlconfig_field_replace_handler_uninstall($def) {
  if (title_field_replacement_enabled($def['entity_type'], $def['bundle'], $def['field'])) {
    title_field_replacement_toggle($def['entity_type'], $def['bundle'], $def['field']);
  }  
}