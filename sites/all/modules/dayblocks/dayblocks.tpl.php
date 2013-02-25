<?php	
	if (empty($title)) {
  		$title = t('Daily Itinerary');
	}
	
	global $base_url;

?>

<!-- begin list of days -->
<section>
<br/>
  <h5><?php print $title; ?> <span class="more">&ndash; <a href="blog.html">View Complete Itinerary &raquo;</a></span></h5>

	<!-- begin post carousel -->
  	<ul class="post-carousel">

    <?php foreach ($days as $key => $day): ?>
      	<li class="entry">
      	
        <div class="entry-body">
           <h4 class="entry-title"><a href="<?php print($base_url.'/day/'.$key.'/'.$model); ?>"><?php print 'Day '.$key; ?></a></h4>
           <div class="entry-content">
         <?php 
         		if(isset($nids[$key])) {
	         			foreach($nids[$key] as $n) {
    	     				$node = node_load($n);
        	 				print $node->title;	
        	 				}
        	 		} else { //no destination specified
        	 			print "No travel";
        	 		}          
          ?>
          	</div>
			<!-- end entry content -->
        	</div>
      </li>
    <?php endforeach; ?>

  </ul>
  <!-- end post carousel -->
</section>
<!-- end latest posts -->