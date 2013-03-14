<?php

function yamlconfig_vocabulary_handler_validate($def) {
  if (!module_exists('taxonomy')) {
    return FALSE;
  }
  if (empty($def['name'])) {
    return FALSE;
  }
  if (empty($def['machine_name'])) {
    return FALSE;
  }
}

function yamlconfig_vocabulary_handler_create($def) {
  $test_vocab = taxonomy_vocabulary_machine_name_load($def['machine_name']);
  if (empty($test_vocab)) {
    $vocab = (object) $def;
    taxonomy_vocabulary_save($vocab);
  }
  // yes, it's silly to do the access here but it's hard because
  // the taxonomy access requires the VID which is not available
  // until it's saved
  if (!empty($def['access'])) {
    foreach ($def['access'] as $role_name => $perms) {
      $permissions = array();
      foreach ($perms as $perm) {
        $permissions[] = $perm . ' terms in ' . $vocab->vid;
      }
      $role = user_role_load_by_name($role_name);
      user_role_grant_permissions($role->rid, $permissions);
    }
  }
}

function yamlconfig_vocabulary_handler_refresh($def) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($def['machine_name']);
  if (!empty($vocabulary)) {
    $def += (array) $vocabulary;
  }
  $vocab = (object) $def;
  taxonomy_vocabulary_save($vocab);
  if (!empty($def['access'])) {
    foreach ($def['access'] as $role_name => $perms) {
      $permissions = array();
      foreach ($perms as $perm) {
        $permissions[] = $perm . ' terms in ' . $vocab->vid;
      }
      $role = user_role_load_by_name($role_name);
      user_role_grant_permissions($role->rid, $permissions);
    }
  }
}

function yamlconfig_vocabulary_handler_uninstall($def) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($def['machine_name']);
  if (!empty($def['access'])) {
    foreach ($def['access'] as $role_name => $perms) {
      $permissions = array();
      foreach ($perms as $perm) {
        $permissions[] = $perm . ' terms in ' . $vocabulary->vid;
      }
      $role = user_role_load_by_name($role_name);
      user_role_revoke_permissions($role->rid, $permissions);
    }
  }
  taxonomy_vocabulary_delete($vocabulary->vid);
}