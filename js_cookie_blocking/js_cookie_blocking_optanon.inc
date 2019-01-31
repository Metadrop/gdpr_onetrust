<?php

/**
 * JsCookieBlocking implements the onetrust API helpers to block cookies.
 */
class JsCookieBlocking {

  private $optanonjs;
  private $insertscript;
  private $inserthtml;

  /**
   * Implement class construct.
   */
  private function __construct() {

  }

  /**
   * Create an singleton factory object.
   */
  public static function instance() {
    static $inst = NULL;
    if ($inst === NULL) {
      $inst = new JsCookieBlocking();
    }
    return $inst;
  }

  /**
   * Verify the JS file and insert to the insertscript API.
   */
  public function generateOptanons($thjs) {
    if ($this->isExistJs($thjs['data']) === TRUE) {
      $this->optanonjs[] = $thjs;
      $this->optanonInsertscript($thjs['data'], $thjs['gdpr_onetrust']['group']);
    }
  }

  /**
   * Implment the oneTrust optanon Insertscript helper function.
   */
  public function optanonInsertscript($js_path, $js_group, $position = "head", $nobase = FALSE, $addjs = FALSE) {
    global $base_url;
    $baseurl = ($nobase == TRUE) ? $base_url . '/' : '';
    $optanonjs = 'Optanon.InsertScript(\'' . $baseurl
    . $js_path . '\', \'' . $position . '\', null, null, ' . $js_group . ' ); ';
    if ($addjs === FALSE) {
      $this->insertscript .= $optanonjs;
    }
    else {
      $this->optanoPublishScriptInline($optanonjs);
    }
  }

  /**
   * Implment the oneTrust optanon Insertscript helper function.
   */
  public function optanonInserthtml($element, $selector, $groupid, $addjs = FALSE) {
    $addhtml = 'Optanon.InsertHtml(\'' . $element
      . '\', \'' . $selector . '\', null, null, ' . $groupid . '); ';
    if ($addjs === FALSE) {
      $this->inserthtml .= $addhtml;
    }
    else {
      $this->optanoPublishScriptInline($addhtml);
    }
  }

  /**
   * Publish the optanon functions as inline script.
   */
  private function optanoPublishScriptInline($data) {
    if ($this->isGdprScope() === TRUE) {
      drupal_add_js($data,
        array(
          'type' => 'inline',
          'scope' => 'header',
          'weight' => 5,
        ));
    }
  }

  /**
   * Verify the Javascript file from the config array.
   */
  private function isExistJs($jsdata) {
    if (is_array($this->optanonjs)) {
      foreach ($this->optanonjs as $key => $js) {
        if (isset($js['data']) && $js['data'] === $jsdata) {
          return FALSE;
        }
      }
    }
    return TRUE;
  }

  /**
   * Implement the optanon wrapper function to page head section.
   */
  public function optanoPublishScript() {
    if ($this->isGdprScope() == TRUE) {
      drupal_add_js('function OptanonWrapper() { gdprDelete().assignCookie(); ' . $this->insertscript . $this->inserthtml . '}',
      array(
        'type' => 'inline',
        'scope' => 'header',
        'weight' => 5,
      ));
    }
  }

  /**
   * Check the current language in GDPR Scopr or not.
   */
  public function isGdprScope() {
    global $language;
    $language_list = language_list();
    if (count($language_list) == 1 && !is_null(variable_get('gdpr_onetrust_compliance_uuid'))) {
      $current_language_uuid = variable_get('gdpr_onetrust_compliance_uuid');
    }
    else {
      $current_language_uuid = variable_get('gdpr_onetrust_compliance_uuid_' . $language->language);
    }
    return empty($current_language_uuid) ? FALSE : TRUE;
  }

}
