<?php

namespace Drupal\gdpr_onetrust\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Language\LanguageManager;

/**
 * Build configuration form.
 */
class GDPROneTrustForm extends FormBase {

  /**
   * Get formid.
   */
  public function getFormId() {
    return 'gdpr_onetrust_admin_settings';
  }

  /**
   * {@inheritdoc}
   */
  public function getEditableConfigNames() {
    return ['gdpr_onetrust.settings'];
  }

  /**
   * Verify the compatibility with previous version.
   */
  public function getGdprConfigInfo() {
    $languages = \Drupal::languageManager()->getLanguages();
    $config = $this->config('gdpr_onetrust.settings');
    if (count($languages) == 1 && !is_null($config->get('gdpr_onetrust_compliance_uuid'))) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Build configuration form.
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $languages = \Drupal::languageManager()->getLanguages();
    $config = $this->config('gdpr_onetrust.settings');
    foreach ($languages as $language) {
      $lang_id = $language->getId();
      $field_name = 'gdpr_onetrust_compliance_uuid_' . $lang_id;
      if ($this->getGdprConfigInfo()) {
        $field_name = 'gdpr_onetrust_compliance_uuid';
      }
      $form[$field_name] = [
        '#type' => 'textfield',
        '#title' => t('UUID for the language') . ' - ' . $language->getName(),
        '#default_value' => $config->get($field_name),
        '#description' => t('Sets the UUID provided by One Trust. This is language dependent.'),
      ];
    }
    $form['submit'] = ['#type' => 'submit', '#value' => t('Submit')];
    return $form;
  }

  /**
   * Validate config form.
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    $gdpr_onetrust_compliance_uuid = $form_state->getValue('gdpr_onetrust_compliance_uuid');
    $languages = \Drupal::languageManager()->getLanguages();
    foreach ($languages as $language) {
      $lang_id = $language->getId();
      $field_name = 'gdpr_onetrust_compliance_uuid_' . $lang_id;
      if ($this->getGdprConfigInfo()) {
        $field_name = 'gdpr_onetrust_compliance_uuid';
      }
      $form_value = $form_state->getValue($field_name);

      if (!empty($form_value) && preg_match(GDPR_ONETRUST_UUID_REGEX, $form_value) != 1) {
        $error_message = 'Please provide the Valid UUID for ' . $language->getName();
        $form_state->setErrorByName($field_name, $error_message);
      }
    }
  }

  /**
   * Form submit handler.
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $languages = \Drupal::languageManager()->getLanguages();
    foreach ($languages as $language) {
      $lang_id = $language->getId();
      $field_name = 'gdpr_onetrust_compliance_uuid_' . $lang_id;
      if ($this->getGdprConfigInfo()) {
        $field_name = 'gdpr_onetrust_compliance_uuid';
      }
      $form_value = $form_state->getValue($field_name);
      $this->configFactory->getEditable('gdpr_onetrust.settings')
        ->set($field_name, $form_value)
        ->save();
    }
    drupal_set_message('GDPR Onetrust Configuration has been saved.');
  }

}
