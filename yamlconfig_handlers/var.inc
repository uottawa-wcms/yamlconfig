<?php

function yamlconfig_var_handler_create($def) {
  foreach ($def as $key => $value) {
    variable_set($key, $value);
  }
}

function yamlconfig_var_handler_update($def) {
  yamlconfig_var_handler_create($def);
}

function yamlconfig_var_handler_uninstall($def) {
  foreach ($def as $key => $value) {
    variable_del($key);
  }
}

function yamlconfig_var_handler_list() {
  return db_select('variable')
      ->fields('variable', array('name'))
      ->execute()
      ->fetchAllKeyed(0,0);
}

function yamlconfig_var_handler_export($key) {
  return array(
    $key => variable_get($key),
  );
}