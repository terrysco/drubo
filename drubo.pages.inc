<?php
// $Id$

/**
 * unbind weibo account
 * @param (array) $form_state
 * @param (object) $ac
 */
function drubo_remove_confirm($form_state) {
  global $user;
  if ($data = db_fetch_object(db_query('SELECT uid FROM {drubo} WHERE uid = %d', $user->uid))) {
    $form['uid'] = array('#type' => 'value', '#value' => $user->uid);
    return confirm_form($form,
                    t('Unbind weibo account'),
                    'sns/remove',
                    t('Are you sure to unbind your weibo account?'),
                    t('Confirm'),
                    t('Cancel'));
  } else {
    drupal_access_denied();
    exit;
  }
}

function drubo_remove_confirm_submit($form, &$form_state) {
  global $user;
  db_query('DELETE FROM {drubo} WHERE uid = %d', $form_state['values']['uid']);
  db_query("DELETE FROM {authmap} WHERE uid = %d AND module = '%s'", $form_state['values']['uid'], 'drubo');
  drupal_set_message(t('Unbind successfully!'));
  $form_state['redirect'] = 'user';
}

function drubo_profile_page($account) {
  if ($drubo = drubo_load($account->uid)) {
    module_load_include('inc', 'drubo', 'drubo.sdk');
    $c = new WeiboClient(
          DRUBO_DEFAULT_API_KEY,
          DRUBO_DEFAULT_API_SECRET,
          $drubo->oauth_token,
          $drubo->oauth_token_secret
    );
    $info = $c->show_user($drubo->weibo_id);
    $output = drupal_get_form('drubo_tweet_form');
    $output .= theme('drubo_profile', $info);
    return $output;
  }
}

function drubo_tweet_form() {
  $form['tweet'] = array(
    '#type' => 'textarea',
    '#rows' => 3,
    '#cols' => 30,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Post'),
  );
  return $form;
}

function drubo_tweet_form_submit($form, &$form_state) {
  drubo_post_tweet($form_state['values']['tweet']);
  drupal_set_message(t('Post tweet successfully!'));
}

