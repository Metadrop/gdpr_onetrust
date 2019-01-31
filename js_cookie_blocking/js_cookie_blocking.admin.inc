<?php

/**
 * @file
 * This file provides administration form for the module.
 */

/**
 * Implement configuration form.
 */
function js_cookie_blocking_admin_form() {
  $form['js_cookie_blocking_external_js_cookie'] = array(
    '#type' => 'textarea',
    '#title' => t('Javascripts URL with cookie category'),
    '#default_value' => variable_get('js_cookie_blocking_external_js_cookie', ''),
    '#description' => t('Add Javascript URL along with the cookie category separated by | symbol. The cookie category values should be 2 for Performance cookie, 3 for Functional cookie, 4 for targetting cookie and 8 for media cookie. Update one JS url on each row. Example:/pathtojs/jsfilename.js|2'),
  );

  return system_settings_form($form);
}
