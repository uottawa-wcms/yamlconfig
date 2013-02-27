<?php

function yamlconfig_permission_handler_validate($def) {
  if (empty($def['role'])) {
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
  $role = user_role_load_by_name($def['role']);
  $def['rid'] = $role->rid;
  if (!is_array($def['permissions'])) {
    $def['permissions'] = array($def['permissions']);
  }
}

function yamlconfig_permission_handler_create($def) {
  user_role_grant_permissions($def['rid'], $def['permissions']);
}

function yamlconfig_permission_handler_refresh($def) {
  yamlconfig_permission_handler_create($def);
}

function yamlconfig_permission_handler_disable($def) {
  user_role_revoke_permissions($def['rid'], $def['permissions']);
}
