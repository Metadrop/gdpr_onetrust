<?php

namespace Drupal\gdpr_onetrust\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides a 'Onetrust' Block.
 *
 * @Block(
 *   id = "onetrust_footer",
 *   admin_label = @Translation("One Trust Cookie Settings"),
 *   category = @Translation("GDPR Onetrust"),
 * )
 */
class OneTrustCookieSettings extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    return [
      '#markup' => "<a class='optanon-toggle-display'>" . t('Cookie Settings') . "</a>",
    ];
  }

}
