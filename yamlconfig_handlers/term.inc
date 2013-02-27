<?php

function yamlconfig_term_handler_validate($def) {
  if (!module_exists('taxonomy')) {
    return FALSE;
  }
  if (empty($def['name'])) {
    return FALSE;
  }
  if (empty($def['vocabulary'])) {
    return FALSE;
  }
  if (empty(taxonomy_vocabulary_machine_name_load($def['vocabulary']))) {
    return FALSE;
  }
}

function yamlconfig_term_handler_preprocess($def) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($def['vocabulary']);
  $def['vid'] = $vocabulary->vid;
}

function yamlconfig_term_handler_create($def) {
  taxonomy_term_save((object) $def);
}

function yamlconfig_term_handler_refresh($def) {
  $tid = _yamlconfig_term_find_id($def['vocabulary'], $def['name']);
  if (!empty($tid)) {
    $def->tid = $tid;
  }
  taxonomy_term_save((object) $def);
}

function yamlconfig_term_handler_uninstall($def) {
  taxonomy_term_delete(_yamlconfig_term_find_id($def['vocabulary'], $def['name']));
}

function _yamlconfig_term_find_id($vocabulary_name, $term_name) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);
  if (empty($vocabulary)) {
    return FALSE;
  } else {
    $rs = db_query('SELECT tid FROM {taxonomy_term_data} WHERE name = :name AND vid = :vid', array(
      ":name" => $term_name,
      ":vid" => $vocabulary->vid,
    ));
    return $rs->fetchField();
  }
}