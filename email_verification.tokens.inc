<?php

/**
 * @file
 * Builds placeholder replacement tokens for email verification data.
 */

/**
 * Implements hook_token_info().
 */
function email_verification_token_info() {
  $types['email-verification'] = array(
    'name' => t('Email verification'),
    'description' => t('Tokens related to email verification'),
    'needs-data' => 'email-verification',
  );

  // @see email_verification_tokens()
  $email_verification['verification-code'] = array(
    'name' => t('Verification Code'),
    'description' => t('The verification Code when registering a user account. This token is only available registering a user account.'),
    'restricted' => TRUE,
  );
  $email_verification['verification-url'] = array(
    'name' => t('Verification URL'),
    'description' => t('The verification URL when registering a user account. This token is only available registering a user account.'),
    'restricted' => TRUE,
    'type' => 'url',
  );

  return array(
    'types' => $types,
    'tokens' => array('email-verification' => $email_verification),
  );
}

/**
 * Implements hook_tokens().
 */
function email_verification_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  if ($type == 'email-verification' && !empty($data['email-verification'])) {
    $email_verification = $data['email-verification'];
    foreach ($tokens as $name => $original) {
      switch ($name) {

        // These tokens are default variations on the chained tokens handled below.
        case 'verification-code':
          $replacements[$original] = !empty($email_verification['verification-code']) ? $email_verification['verification-code'] : '';
          break;

        case 'verification-url':
          $replacements[$original] = !empty($email_verification['verification-code']) ? $email_verification['verification-code'] : '';
          break;
      }
    }

  }

  return $replacements;
}
