<?php

function yamlconfig_text_format_handler_validate($def) {
  if (!module_exists('filter')) {
    return FALSE;
  }
  if (empty($def['format'])) {
    return FALSE;
  }
  if (empty($def['name'])) {
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_text_format_handler_preprocess(&$def) {
  $def += array(
    'status' => 1,
  );
}

function yamlconfig_text_format_handler_create($def) {
  filter_format_save($def);
}

function yamlconfig_text_format_handler_refresh($def) {
  yamlconfig_text_format_handler_create($def);
}

function yamlconfig_text_format_handler_disable($def) {
  $def['status'] = 0;
  filter_format_save($def);
}
