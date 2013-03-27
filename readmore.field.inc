<?php

/**
 * @file
 * Field formatter hooks to implement a readmore.
 */

/**
 * Implements hook_field_formatter_info().
 */
function readmore_field_formatter_info() {
  return array(
    'readmore' => array(
      'label' => t('Read more'),
      'field types' => array(
        'text',
        'text_long',
        'text_with_summary',
      ),
      'settings' => array(
        'readmore_trim_length' => 500,
        'readmore_ellipsis' => TRUE,
        'readmore_wordsafe' => FALSE,
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function readmore_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  if ($display['type'] == 'readmore') {
    $element['readmore_trim_length'] = array(
      '#title' => t('Trim length'),
      '#type' => 'textfield',
      '#size' => 10,
      '#default_value' => $settings['readmore_trim_length'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#required' => TRUE,
    );
    $element['readmore_ellipsis'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add ellipsis'),
      '#default_value' => $settings['readmore_ellipsis'],
    );
    $element['readmore_wordsafe'] = array(
      '#type' => 'checkbox',
      '#title' => t('Truncate on a word boundary'),
      '#default_value' => $settings['readmore_wordsafe'],
    );
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function readmore_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = '';

  if ($display['type'] == 'readmore') {
    $summary[] = t('Trim length: @length', array('@length' => $settings['readmore_trim_length'])) . "\n";
    $summary[] = $settings['readmore_ellipsis'] ? t('Add ellipsis') : t('Do not add ellipsis');
    $summary[] = $settings['readmore_wordsafe'] ? t('Safe words') : t('Do not safe words');
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function readmore_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($display['type']) {
    case 'readmore':
      drupal_add_js(READMORE_MODULE_PATH . '/js/readmore.js');
      foreach ($items as $delta => $item) {
        $output = _text_sanitize($instance, $langcode, $item, 'value');
        $output = readmore_divide_string($output, isset($item['format']) ? $item['format'] : NULL, $display['settings']['readmore_trim_length'], $display['settings']['readmore_wordsafe']);
        if (is_array($output)) {
          $output['ellipsis'] = $display['settings']['readmore_ellipsis'];
          $element[$delta] = array(
            '#markup' => theme('readmore', $output),
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
