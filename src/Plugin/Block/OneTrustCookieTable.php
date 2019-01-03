<?php

namespace Drupal\gdpr_onetrust\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides a 'Onetrust' Block.
 *
 * @Block(
 *   id = "onetrust_header",
 *   admin_label = @Translation("One Trust Cookie Table"),
 *   category = @Translation("GDPR Onetrust"),
 * )
 */
class OneTrustCookieTable extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    return [
      '#markup' => '<div id="optanon-cookie-policy"></div>',
    ];
  }

}
