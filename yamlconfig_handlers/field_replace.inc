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

function yamlconfig_field_replace_handler_preprocess(&$def) {
  if (!is_array($def['field'])) {
    $def['field'] = array($def['field']);
  }
}

function yamlconfig_field_replace_handler_create($def) {
  foreach ($def['field'] as $field) {
    title_field_replacement_toggle($def['entity_type'], $def['bundle'], $field);
  }
}

function yamlconfig_field_replace_handler_refresh($def) {
  foreach ($def['field'] as $field) {
    if (!title_field_replacement_enabled($def['entity_type'], $def['bundle'], $field)) {
      title_field_replacement_toggle($def['entity_type'], $def['bundle'], $field);
    }
  }
}

function yamlconfig_field_replace_handler_uninstall($def) {
  foreach ($def['field'] as $field) {
    if (title_field_replacement_enabled($def['entity_type'], $def['bundle'], $field)) {
      title_field_replacement_toggle($def['entity_type'], $def['bundle'], $field);
    }
  }
}