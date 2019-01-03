<?php

/**
 * @file
 * This file provides administration form for the module.
 */

/**
 * Provides form for Onetrust configurations values.
 */
function gdpr_onetrust_compliance_admin_form($form_state) {
  $language_list = language_list();
  $language_list_count = count($language_list);
  foreach ($language_list as $language_key => $language_details) {
    $form_field = gdpr_onetrust_compliance_gnerate_fieldname($language_list_count, $language_key);
    $form[$form_field] = array(
      '#type' => 'textfield',
      '#title' => t('UUID for the language') . ' - ' . $language_details->name,
      '#default_value' => variable_get($form_field, ''),
      '#description' => t('The UUID provided by One Trust for the site. This is language dependent.'),
    );
  }
  $form['#validate'][] = 'gdpr_onetrust_compliance_admin_form_validate';

  return system_settings_form($form);
}

/**
 * Validate the submitted UUID.
 */
function gdpr_onetrust_compliance_admin_form_validate(&$form, &$form_state) {

  $form_values = $form_state['values'];
  $language_list = language_list();
  $language_list_count = count($language_list);
  foreach ($language_list as $language_key => $language_details) {
    $form_field = gdpr_onetrust_compliance_gnerate_fieldname($language_list_count, $language_key);
    $value = $form_values[$form_field];

    if (gdpr_onetrust_compliance_isvalid_uuid($value) == FALSE) {
      form_set_error($form_field, t('Please provide a Valid UUID for:') . $language_details->name);
    }

  }
}

/**
 * Create a field name.
 */
function gdpr_onetrust_compliance_gnerate_fieldname($language_list_count, $language_key) {

  if ($language_list_count == 1 && !is_null(variable_get('gdpr_onetrust_compliance_uuid'))) {
    return 'gdpr_onetrust_compliance_uuid';
  }
  else {
    return 'gdpr_onetrust_compliance_uuid_' . $language_key;
  }
}
