<?php


function yamlconfig_widget_instance_handler_validate($def) {
  if (empty($def['type'])) {
    return FALSE;
  }
  if (empty($def['ref'])) {
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_widget_instance_handler_preprocess(&$def) {
  $def += array(
    'weight' => 0,
  );
}

function yamlconfig_widget_instance_handler_create($def) {
  yamlconfig_store_value('widget_instance', $def['ref'], $def);
}

function yamlconfig_widget_instance_handler_refresh($def) {
  yamlconfig_widget_instance_handler_create($def);
}

function yamlconfig_widget_instance_handler_uninstall($def) {
  yamlconfig_remove_value('widget_instance', $def['ref']);
}

