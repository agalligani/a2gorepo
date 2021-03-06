<!DOCTYPE HTML>
<!--[if IE 8]> <html class="ie8 no-js"> <![endif]-->
<!--[if (gte IE 9)|!(IE)]><!--> <html class="no-js"> <!--<![endif]-->
  <head profile="<?php print $grddl_profile; ?>">
    <?php print $head; ?>
    <title><?php print $head_title; ?></title>
    <?php print $styles; ?>
    <?php print $scripts; ?>
    <!--[if IE 8]><script src="<?php print base_path() . path_to_theme(); ?>/js/respond.min.js" type="text/javascript"></script><![endif]--> <!-- Respond -->

    <?php
    $bg_image = 'none';

    $theme_style = theme_get_setting('layout_style', 'finesse');
    if ($theme_style == 'boxed') {
      $classes .= ' boxed';
      $box_image = theme_get_setting('boxed_bg_img', 'finesse');

      if ($box_image != 'none') {
        $bg_image = 'url("' . base_path() . path_to_theme() . '/images/background-patterns/boxed/' . $box_image . '") !important';
      }

      $bg_color = theme_get_setting('boxed_bg_color', 'finesse');
    } else {

      $wide_image = theme_get_setting('wide_bg_img', 'finesse');
      if ($wide_image != 'none') {
        $bg_image = 'url("' . base_path() . path_to_theme() . '/images/background-patterns/wide/' . $wide_image . '") !important';
      }
    }
    ?>

    <style type="text/css">
      body{

        background-image: <?php print $bg_image; ?>;
        <?php if (!empty($bg_color) && $bg_color != 'none'): ?>
          background: <?php print $bg_color; ?> !important;
        <?php endif; ?>
      }
    </style>

  </head>


  <body class="<?php print $classes; ?>" <?php print $attributes; ?>>
  <div id="fb-root"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/en_US/all.js#xfbml=1&appId=147584411956811";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));
</script>
    <div id="skip-link">
      <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
    </div>
    <?php print $page_top; ?>
    <?php print $page; ?>
    <?php print $page_bottom; ?>
  </body>
</html>
