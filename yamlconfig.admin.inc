<?php

function yamlconfig_admin_export_page($form, &$form_state) {
  $handlers = array(
    '' => 'Select one...',
  );
  $form['container']['#prefix'] = '<div id="yaml-export-form">';
  $handlers += yamlconfig_export_type_list();
  ksort($handlers);
  $type = isset($form_state['values']['export_type']) ?
      $form_state['values']['export_type'] : reset(array_keys($handlers));
  $form['container']['export_type'] = array(
    '#title' => t('Object Type'),
    '#type' => 'select',
    '#description' => t('Select the type of object you would like to export'),
    '#options' => $handlers,
    '#default_value' => $type,
    '#ajax' => array(
      'callback' => 'yamlconfig_admin_rebuild_export',
      'wrapper' => 'yaml-export-form',
      'method' => 'replace',
    ),
  );
  if (!empty($type)) {
    $objects = yamlconfig_export_list($type);
    $form['container']['export_option'] = array(
      '#title' => t('Object Key'),
      '#type' => 'select',
      '#description' => t('Select the object you would like to export'),
      '#options' => array('' => t('Select one...')) + $objects[$type],
      '#ajax' => array(
        'callback' => 'yamlconfig_admin_rebuild_export',
        'wrapper' => 'yaml-export-form',
        'method' => 'replace',
      ),
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
  );
  if (!empty($form_state['values']['export_option'])) {
    $value = t('We were unable to export the requested object');
    $export = yamlconfig_export_object($type, $form_state['values']['export_option']);
    if (!empty($export)) {
      $value = $export;
    }
    $form['container']['name'] = array(
      '#type' => 'markup',
      '#markup' => '<p>Recommended Name:<br /><strong><em>mymodule</em>.' . $type . '.' . $form_state['values']['export_option'] . '.yml</strong>',
    );
    $form['container']['export'] = array(
      '#title' => t('Exported Object'),
      '#type' => 'textarea',
      '#value' => $value,
      '#rows' => 20,
      '#attributes' => array(
        'style' => 'font-family: Courier New',
      ),
    );
  }
  $form['container']['#suffix'] = '</div>';
  return $form;
}

function yamlconfig_admin_export_page_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

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