<?php

/**
 * @file drubo_profile.tpl.php
 * Default theme implementation for rendering the profile of a given user.
 *
 * Available variables:
 * $info: Array of profile information of sina weibo.
 */
?>
<?php print theme('image', $info['profile_image_url'], $info['screen_name'], $info['screen_name'], array(), false); ?>
<div><?php print $info['screen_name']; ?> <span><?php print $info['description']; ?></span></div>
<ul>
  <li>Location: <?php print $info['location']; ?></li>
  <li>Followers: <?php print $info['followers_count']; ?></li>
  <li>Friends: <?php print $info['friends_count']; ?></li>
  <li>Tweets: <?php print $info['statuses_count']; ?></li>
</ul>

