<?php

/**
 * @file
 * Field formatter hooks to implement a more_text.
 */

/**
 * Implements hook_field_formatter_info().
 */
function more_text_field_formatter_info() {
  return array(
    'more_text' => array(
      'label' => t('More text'),
      'field types' => array(
        'text',
        'text_long',
        'text_with_summary',
      ),
      'settings' => array(
        'trim_length' => 300,
        'ellipsis' => TRUE,
        'wordsafe' => FALSE,
      ),
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
    $element['ellipsis'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add ellipsis'),
      '#default_value' => $settings['ellipsis'],
    );
    $element['wordsafe'] = array(
      '#type' => 'checkbox',
      '#title' => t('Truncate on a word boundary'),
      '#default_value' => $settings['wordsafe'],
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
    $summary[] = t('Trim length: @length', array('@length' => $settings['trim_length'])) . "\n";
    $summary[] = $settings['ellipsis'] ? t('Add ellipsis') : t('Do not add ellipsis');
    $summary[] = $settings['wordsafe'] ? t('Safe words') : t('Do not safe words');
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function more_text_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($display['type']) {
    case 'more_text':
      drupal_add_js(MORE_TEXT_MODULE_PATH . '/js/more_text.js');
      foreach ($items as $delta => $item) {
        $output = _text_sanitize($instance, $langcode, $item, 'value');
        $output = more_text_divide_string($output, isset($item['format']) ? $item['format'] : NULL, $display['settings']['trim_length'], $display['settings']['wordsafe']);
        if (is_array($output)) {
          $output['ellipsis'] = $display['settings']['ellipsis'];
          $element[$delta] = array(
            '#markup' => theme('more_text', $output),
          );
        }
        else {
          $element[$delta] = array(
            '#markup' => $output,
          );
        }
      }
      break;
  }

  return $element;
}
