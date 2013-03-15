<?php

function yamlconfig_admin_status_page($form, &$form_state) {
  $form['refresh'] = array(
    '#type' => 'submit',
    '#value' => t('Restore Configuration'),
    '#submit' => array('yamlconfig_admin_refresh_configuration'),
  );
  $config = yamlconfig_display_config();
  $rows = array();
  $header = array(
    'key' => t('Config Key'),
    'type' => t('Object Type'),
    'valid' => t('Valid?'),
    'parser' => t('Parser?'),
    'create' => t('Create?'),
    'refresh' => t('Refresh?'),
  );
  foreach ($config as $obj) {
    $row = array();
    $good = $obj['valid'] && $obj['parser'] && $obj['refresh'] && $obj['create'];
    if ($good) {
      $row['style'] = 'background-color: #CFC';
    } else {
      $row['style'] = 'background-color: #FCC';
    }
    $row['data']['key'] = '<span title="' . $obj['file'] . '">' . $obj['module'] . '.' . $obj['type'] . '.' . $obj['key'] . '</span>';
    $row['data']['type'] = $obj['type'];
    $row['data']['valid'] = $obj['valid'] ? t('Yes') : t('No');
    $row['data']['parser'] = $obj['parser'] ? t('Yes') : t('No');
    $row['data']['create'] = $obj['create'] ? t('Yes') : t('No');
    $row['data']['refresh'] = $obj['refresh'] ? t('Yes') : t('No');
    $rows[] = $row;
  }
  $form['yaml_info'] = array(
    '#type' => 'markup',
    '#markup' => theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'empty' => t('No configuration objects found'),
    ))
  );
  return $form;
}

function yamlconfig_admin_refresh_configuration($form, &$form_state) {
  yamlconfig_refresh_config();
  drupal_set_message(t('Managed configuration has been refreshed to defaults.'));
}