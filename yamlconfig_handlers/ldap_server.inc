<?php

function yamlconfig_ldap_server_handler_validate($def) {
  if (empty($def['sid'])) {
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_ldap_server_handler_preprocess(&$def) {
  $def += array(
    'status' => 1,
  );
}

function yamlconfig_ldap_server_handler_create($def) {
  db_merge('ldap_server')
    ->fields($def)
    ->key(array('sid' => $def['sid']))
    ->execute();
}

function yamlconfig_ldap_server_handler_refresh($def) {
  yamlconfig_ldap_server_handler_create($def);
}

function yamlconfig_ldap_server_handler_disable($def) {
  $def['status'] = 0;
  yamlconfig_ldap_server_handler_create($def);
}

function yamlconfig_ldap_server_handler_uninstall($def) {
  db_delete('ldap_server')
      ->condition('sid', $def['sid'])
      ->delete();
}