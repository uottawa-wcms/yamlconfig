<?php

function yamlconfig_permission_handler_validate($def) {
  if (empty($def['roles'])) {
    return FALSE;
  }
  if (empty($def['permissions'])) {
    return FALSE;
  }
  $perms = user_permission_get_modules();
  if (!is_array($def['permissions'])) {
    if (empty($perms[$def['permissions']])) {
      return FALSE;
    }
  } else {
    foreach ($def['permissions'] as $permission) {
      if (empty($perms[$permission])) {
        return FALSE;
      }
    }
  }
}

function yamlconfig_permission_handler_preprocess(&$def) {
  if (!is_array($def['roles'])) {
    $def['roles'] = array($def['roles']);
  }
  $def['rids']= array();
  foreach ($def['roles'] as $role) {
    $obj = user_role_load_by_name($role);
    $def['rids'][] = $obj->rid;
  }
  if (!is_array($def['permissions'])) {
    $def['permissions'] = array($def['permissions']);
  }
}

function yamlconfig_permission_handler_create($def) {
  foreach ($def['rids'] as $rid) {
    user_role_grant_permissions($rid, $def['permissions']);
  }
}

function yamlconfig_permission_handler_refresh($def) {
  yamlconfig_permission_handler_create($def);
}

function yamlconfig_permission_handler_disable($def) {
  foreach ($def['rids'] as $rid) {
    user_role_revoke_permissions($rid, $def['permissions']);
  }
}
