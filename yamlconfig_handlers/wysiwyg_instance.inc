<?php


function yamlconfig_wysiwyg_instance_handler_validate($def) {
  if (empty($def['ref'])) {
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_wysiwyg_instance_handler_preprocess(&$def) {
  $def += array(
    'weight' => 0,
  );
}

function yamlconfig_wysiwyg_instance_handler_create($def) {
  yamlconfig_store_value('wysiwyg_instance', $def['ref'], $def);
}

function yamlconfig_wysiwyg_instance_handler_refresh($def) {
  yamlconfig_wysiwyg_instance_handler_create($def);
}

function yamlconfig_wysiwyg_instance_handler_uninstall($def) {
  yamlconfig_remove_value('wysiwyg_instance', $def['ref']);
}

