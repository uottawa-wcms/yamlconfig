<?php

function yamlconfig_permission_handler_validate($def) {
  if (empty($def['roles'])) {
    print 'no roles';
    return FALSE;
  }
  if (empty($def['permissions'])) {
    print 'no perms';
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_permission_handler_preprocess(&$def) {
  if (!is_array($def['roles'])) {
    $def['roles'] = array($def['roles']);
  }
  $def['rids']= array();
  foreach ($def['roles'] as $role) {
    $obj = user_role_load_by_name($role);
    if ($obj) {
      $def['rids'][] = $obj->rid;
    }
  }
  if (!is_array($def['permissions'])) {
    $def['permissions'] = array($def['permissions']);
  }
  $validated = array();
  $perms = user_permission_get_modules();
  foreach ($def['permissions'] as $perm) {
    if (!empty($perms[$perm])) {
      $validated[] = $perm;
    }
  }
  $def['valid_permissions'] = $validated;
}

function yamlconfig_permission_handler_create($def) {
  foreach ($def['rids'] as $rid) {
    user_role_grant_permissions($rid, $def['valid_permissions']);
  }
}

function yamlconfig_permission_handler_refresh($def) {
  yamlconfig_permission_handler_create($def);
}

function yamlconfig_permission_handler_disable($def) {
  foreach ($def['rids'] as $rid) {
    user_role_revoke_permissions($rid, $def['valid_permissions']);
  }
}
