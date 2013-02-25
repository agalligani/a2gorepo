<?php

function tripper_admin_page() {
	$build = array();
	
	$build['text1'] = array(
	'#type' => 'markup',
	'#markup' => '<div>hi</div>',
	);
	
	return $build;
	
}