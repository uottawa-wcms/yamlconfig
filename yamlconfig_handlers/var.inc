<?php

function yamlconfig_role_handler_create($def) {
  foreach ($def as $key => $value) {
    variable_set($key, $value);
  }
}

function yamlconfig_role_handler_update($def) {
  yamlconfig_role_handler_create($def);
}

function yamlconfig_role_handler_uninstall($def) {
  foreach ($def as $key => $value) {
    variable_del($key);
  }
}