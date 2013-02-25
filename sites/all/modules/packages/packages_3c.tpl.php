
<?php
require_once 'packages_filter.tpl.php';
?>

<?php if (!empty($nodes)): ?>
  <!-- begin gallery -->

  <ul id="gallery" class="portfolio-grid clearfix">
    <?php foreach ($nodes as $node) : ?>

      <?php
      $language = $node->language;

      $image_full = '';
      ?>

      <li data-id="id-1" data-type="<?php print portfolio_format_terms('field_portfolio_category', $node); ?>" class="entry one-third">
        <?php
//        dsm($node->uc_product_image);
        $image_uri = isset($node->uc_product_image[$language][0]['uri']) ? $node->uc_product_image[$language][0]['uri'] : 'logo.jpg';
        $image_url = file_create_url($image_uri);
        $style_name = 'package_preview';
        $node_url = url('node/' . $node->nid);
        $node_title = $node->title;
        ?>
        <div class="jcarousel">
          <a class="fancybox" href="<?php print $node_url; ?>" title="<?php print $node->title; ?>"><!-- span class="overlay zoom"></span -->
            <?php print theme('image_style', array('style_name' => $style_name, 'path' => $image_uri)); ?>
          </a>
        </div>
        <h4 class="entry-title"><a href="<?php print $node_url; ?>"><?php print $node_title; ?></a></h4>

      </li>
    <?php endforeach; ?>

  </ul>

<?php endif; ?>
<!-- end gallery -->