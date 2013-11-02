<?php

/**
 * @file
 * Contains \Drupal\readmore\Plugin\field\formatter\ReadmoreFormatter.
 */

namespace Drupal\readmore\Plugin\Field\FieldFormatter;

use Drupal\Core\Field\FieldItemListInterface;
use Drupal\Core\Field\FormatterBase;

/**
 * Plugin implementation of the 'readmore' formatter.
 *
 * @FieldFormatter(
 *   id = "readmore",
 *   label = @Translation("Readmore"),
 *   field_types = {
 *     "text",
 *     "text_long",
 *     "text_with_summary"
 *   },
 *   settings = {
 *     "trim_length" = "500"
 *   }
 * )
 */
class ReadmoreFormatter extends FormatterBase {

  /**
   * {@inheritdoc}
   */
  public function settingsForm(array $form, array &$form_state) {
    $elements = parent::settingsForm($form, $form_state);

    $elements['trim_length'] = array(
      '#type' => 'number',
      '#title' => t('Trim link text length'),
      '#field_suffix' => t('characters'),
      '#default_value' => $this->getSetting('trim_length'),
      '#min' => 1,
      '#description' => t('Leave blank to allow unlimited link text lengths.'),
    );

    return $elements;
  }

  /**
   * {@inheritdoc}
   */
  public function settingsSummary() {
    $summary = array();

    $settings = $this->getSettings();

    if (!empty($settings['trim_length'])) {
      $summary[] = t('Text trimmed to @limit characters', array('@limit' => $settings['trim_length']));
    }
    else {
      $summary[] = t('Text not trimmed');
    }

    return $summary;
  }

  /**
   * {@inheritdoc}
   */
  public function viewElements(FieldItemListInterface $items) {
    $elements = array();
    $max_length = $this->getSetting('trim_length');

    foreach ($items as $delta => $item) {
      $elements[$delta] = array('#markup' => truncate_utf8($item->value, $max_length, FALSE));
    }

    return $elements;
  }
}
