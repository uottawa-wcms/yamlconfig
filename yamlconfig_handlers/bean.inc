<?php


function yamlconfig_bean_handler_validate($def) {
  if (empty($def['label'])) {
    return FALSE;
  }
  if (empty($def['machine_name'])) {
    return FALSE;
  }
}

function yamlconfig_bean_handler_create($def) {
  $type_test = bean_type_load($def['machine_name']);
  if (empty($type_text)) {
    $plugin = _bean_admin_default_plugin();
    $plugin['name'] = '';
    $type = new BeanCustom($plugin);
    $type->type = $def['machine_name'];
    $type->setLabel($def['label']);
    if (!empty($def['description'])) {
      $type->setDescription($def['description']);
    }
    $type->save(TRUE);
  }
}

function yamlconfig_bean_handler_refresh($def) {
  $old_type = bean_type_load($def['machine_name']);
  if (empty($old_type)) {
    yamlconfig_bean_handler_create($def);
  } else {
    $plugin = _bean_admin_default_plugin();
    $plugin['name'] = '';
    $type = new BeanCustom($plugin);
    $type->type = $def['machine_name'];
    $type->setLabel($def['label']);
    if (!empty($def['description'])) {
      $type->setDescription($def['description']);
    } else {
      $type->setDescription($old_type->getDescription());
    }
    $type->save(FALSE);
  }
}

function yamlconfig_bean_handler_uninstall($def) {
    $plugin = _bean_admin_default_plugin();
    $plugin['name'] = '';
    $type = new BeanCustom($plugin);
    $type->type = $def['machine_name'];
    $type->delete();
}