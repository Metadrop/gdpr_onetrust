<?php

/**
 * @file
 * This file provides function to store common JS across all websites.
 */

/**
 * Create an array to update the common JS files.
 */
function js_cookie_blocking_cookie_js_list() {

  return $cookie_js_path = array(
    JS_COOKIE_BLOCKING_PERFORMANCE => array(),
    JS_COOKIE_BLOCKING_FUNCTIONAL => array(),
    JS_COOKIE_BLOCKING_TARGETTING => array(),
    JS_COOKIE_BLOCKING_MEDIA => array(),
  );

}