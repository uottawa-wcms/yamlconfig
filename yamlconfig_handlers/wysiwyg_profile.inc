<?php

function yamlconfig_wysiwyg_profile_handler_validate($def) {
  if (!module_exists('wysiwyg')) {
    return FALSE;
  }
  if (empty($def['format'])) {
    return FALSE;
  }
  return TRUE;
}

function yamlconfig_wysiwyg_profile_handler_preprocess(&$def) {
  $def += array(
    'entity_type' => 'wysiwyg_profile',
  );
}

function yamlconfig_wysiwyg_profile_handler_create($def) {
  db_merge('wysiwyg')
    ->key(array('format' => $def['format']))
    ->fields(array(
      'format' => $def['format'],
      'editor' => $def['editor'],
      'settings' => serialize($def['settings']),
    ))
    ->execute();
}

function yamlconfig_wysiwyg_profile_handler_refresh($def) {
  yamlconfig_wysiwyg_profile_handler_create($def);
}

function yamlconfig_wysiwyg_profile_handler_uninstall($def) {
  db_delete('wysiwyg')
    ->condition('format', $def['format'])
    ->execute();
  wysiwyg_profile_cache_clear();
}

function yamlconfig_wysiwyg_profile_handler_list() {
  return db_select('wysiwyg')
      ->fields('wysiwyg', array('format'))
      ->execute()
      ->fetchAllKeyed(0,0);
}

function yamlconfig_wysiwyg_profile_handler_export($key) {
  $profile = db_select('wysiwyg')
      ->fields('wysiwyg')
      ->condition('format', $key)
      ->execute()
      ->fetchAssoc();
  $profile['settings'] = unserialize($profile['settings']);
  return $profile;
}