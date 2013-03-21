<?php

function yamlconfig_var_handler_create($def) {
  foreach ($def as $key => $value) {
    variable_set($key, $value);
  }
}

function yamlconfig_var_handler_update($def) {
  yamlconfig_var_handler_create($def);
}

function yamlconfig_var_handler_uninstall($def) {
  foreach ($def as $key => $value) {
    variable_del($key);
  }
}