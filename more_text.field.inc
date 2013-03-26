<?php
/**
 * @file
 */

/**
 * Implements hook_field_formatter_info().
 */
function more_text_field_formatter_info() {
  return array(
    'more_text' => array(
      'label' => t('More text'),
      'field types' => array('text', 'text_long', 'text_with_summary'),
      'settings' => array('trim_length' => 300),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function more_text_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  if ($display['type'] == 'more_text') {
    $element['trim_length'] = array(
      '#title' => t('Trim length'),
      '#type' => 'textfield',
      '#size' => 10,
      '#default_value' => $settings['trim_length'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#required' => TRUE,
    );
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function more_text_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = '';

  if ($display['type'] == 'more_text') {
    $summary = t('Trim length') . ': ' . $settings['trim_length'];
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function more_text_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($display['type']) {
    case 'more_text':
      foreach ($items as $delta => $item) {
        $output = _text_sanitize($instance, $langcode, $item, 'value');
        $output = more_text_trim_text($output, $instance['settings']['text_processing'] ? $item['format'] : NULL, $display['settings']['trim_length']);
        $element[$delta] = array('#markup' => $output);
      }
      break;
  }

  return $element;
}
