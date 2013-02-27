<?php

function yamlconfig_wysiwyg_profile_handler_validate($def) {
  if (!module_exists('wysiwyg')) {
    return FALSE;
  }
  if (!isset($def['format'])) {
    return FALSE;
  }
}

function yamlconfig_wysiwyg_profile_handler_preprocess(&$def) {
  $def += array(
    'entity_type' => 'wysiwyg_profile',
  );
}

function yamlconfig_wysiwyg_profile_handler_create($def) {
  db_merge('wysiwyg', 'w')
    ->key(array('format' => $def['format']))
    ->fields(array(
      'editor' => $def['editor'],
      'settings' => $def['settings'],
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