<div class='row'>
	<div class='three-fourths'>

	<?php 	global $base_url; ?>
	<?php 	global $user; ?>
	<?php if (!empty($nodes)): ?>

	<?php 
		foreach ($nodes as $node) {
        	$node_url = url('node/' . $node->nid);
        	$node_title = $node->title;
			print '<h4><a href="'.$node_url.'">'.$node->title.'</a></h4>';
		}
	?>
	<?php else: ?>
	
	<h3>No travel.</h3>
	
	<?php endif; ?>

	<?php if (in_array('administrator', $user->roles)): ?>
	<!-- 	add destination button   -->
		<a class='button' href='<?php print $base_url.'/tripper/'.arg(1).'/'.$trip['model']; ?>'>Add Destinations</a>
	<?php endif; ?>

	</div>



	<!-- build the local nav menu -->
	
	<div class='one-fourth column-last'>

	<nav class='widget'>

		<ul class='menu'>
		
	<?php for($i=1; $i<=$trip['field_number_of_days_value']; $i++) {
		print '<li><a href=\''.$base_url.'/day/'.$i.'/'.$trip['model'].'\'>Day '.$i.'</a></li>';	
		}
	?>
	
		</ul>
	</nav>
</div>


</div>
