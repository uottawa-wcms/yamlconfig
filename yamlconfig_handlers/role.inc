<?php

function yamlconfig_role_handler_validate($def) {
  if (empty($def['name'])) {
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_role_handler_create($def) {
  $existing = array();
  foreach (user_roles() as $role) {
    $existing = $role->name;
  }
  if (!in_array($def['name'], $existing)) {
    user_role_save((object) $def);
  }
}

function yamlconfig_role_handler_refresh($def) {
  yamlconfig_role_handler_refresh($def);
}

function yamlconfig_role_handler_update($def) {
  $def += (array) user_role_load_by_name($def['name']);
  user_role_save((object) $def);
}

function yamlconfig_role_handler_uninstall($def) {
  user_role_delete($def['name']);
}