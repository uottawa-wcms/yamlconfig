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
  if (empty(taxonomy_vocabulary_machine_name_load($def['machine_name']))) {
    taxonomy_vocabulary_save((object) $def);
  }
}

function yamlconfig_vocabulary_handler_refresh($def) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($def['machine_name']);
  if (!empty($vocabulary)) {
    $def += (array) $vocabulary;
  }
  taxonomy_vocabulary_save((object) $def);
}

function yamlconfig_vocabulary_handler_uninstall($def) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($def['machine_name']);
  taxonomy_vocabulary_delete($vocabulary->vid); 
}