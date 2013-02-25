<?php


function tripper_itinerary($day, $trip) {

	$form = drupal_get_form('trip_planner', $day, $trip);
	return $form;
}

function trip_planner($form, &$form_state, $day, $trip) {

        $query = db_select('node', 'n');
        $query->leftJoin('uc_products', 'prod', 'n.nid = prod.nid');
        $query->leftJoin('field_revision_field_number_of_days', 'day_count', 'n.nid = day_count.entity_id');
		
        $trips = $query
                ->fields('n', array('nid', 'sticky', 'created', 'title'))
                ->fields('prod', array('sell_price','model'))
                ->fields('day_count', array('field_number_of_days_value'))
                ->condition('prod.model', $trip)
                ->condition('n.type', 'product')
                ->condition('n.status', 1)
                ->orderBy('n.sticky', 'DESC')
                ->orderBy('n.created', 'DESC')
                ->addTag('node_access')
                ->execute()
                ->fetchAssoc();
	
//	$trip = node_load($nid);
// 
	global $base_url; 
	$node_url = $base_url.'/node/'.$trips['nid'];
 	$form['trip_name'] = array(
 		'#type' => 'markup',
 		'#markup' => '<h4><a href='.$node_url.'>'.$trips['model'].' - '.$trips['title'].'</a></h4>',
 	);	
 	
 	$form['day_count'] = array(
 		'#type' => 'markup',
 		'#markup' => '<h4>Day '.$day.' of '.$trips['field_number_of_days_value'].'</h4>',
 	);	
 	
 	
// build location options
// 
				
	$form['location'] = array(
		'#type'=>'radios',
		'#options' => get_locs_array(),
	);
				
	$form['trip_nid'] = array(
		'#type' => 'hidden',
		'#value' => $trips['nid'],	
	);	
	
	$form['trip_days'] = array(
		'#type' => 'hidden',
		'#value' => $trips['field_number_of_days_value'],
	);
	
	$form['trip_day'] = array(
		'#type' => 'hidden',
		'#value' => $day,
	);

	$form['model'] = array(
		'#type' => 'hidden',
		'#value' => $trips['model'],
	);
// 
// 	$view_name = 'destdrag';
//   	$view = views_get_view($view_name);
// 	
// 	$display_id = 'page';
// 	$args= array($nid);
//   	if (!(!$view || !$view->access($display_id))) {
// 
// 		$form['trip_view'] = array(
// 			'#type' => 'markup',
// 			'#markup' =>   $view->preview($display_id, $args),
// 			);		
//   	}
// 
// 
// 
// 	
// 	$form['dest_lat'] = array(
// 		'#type' => 'hidden',
// 	);	
// 
// 	$form['dest_lng'] = array(
// 		'#type' => 'hidden',
// 	);	
// 
// 
// 	$form['description'] = array(
// 		'#type' => 'markup',
// 		'#markup' => '<div style=\'width: 50%;\'>Type in the name or address of your next destination/location or select "show destinations" to see popular local choices based on the previous saved destination.</div>',	
// 	);	
// 	
// 	$form['loc_map'] = array(
// 		'#type' => 'markup',
// 		'#markup' => '<div id=\'loc-map\' class=\'clearfix\'></div>',	
// 	);	
// 	
// 	$form['location_name'] = array(
// 		'#type' => 'textfield',
// 		'#title' => 'Location name or address:',	
// 	);	
// 
// 	$form['street'] = array(
// // 		'#type' => 'textfield',
// 		'#type' => 'hidden',
// 
// 		'#title' => 'Street:',	
// 	);	
// 	
// 	$form['additional'] = array(
// 		'#type' => 'hidden',
// 		'#title' => 'Line 2:',	
// 	);	
// 	
// 		$form['city'] = array(
// 		'#type' => 'hidden',
// 		'#title' => 'City/Town:',	
// 	);	
// 	
// 		$form['province'] = array(
// 		'#type' => 'hidden',
// 		'#title' => 'State/Province:',	
// 	);	
// 
// 	$form['postal_code'] = array(
// 		'#type' => 'hidden',
// 		'#title' => 'Postal/Zip Code:',	
// 	);	
// 
// 	$form['country'] = array(
// 		'#type' => 'hidden',
// 		'#title' => 'Country:',	
// 	);	
// 
// 	$form['find_location'] = array(
// 		'#type' => 'markup',
// 		'#markup' => '<a href="#" id="get-geo">Find Location</a>',	
// 	);	
// 
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Add to Itinerary',
	);
// 		
	return $form;
}


/**
 * Submit function to add a destination.
 *
 * Adds a submit handler/function to our form to send a successful
 * completion message to the screen.
 */
function trip_planner_submit($form, &$form_state) {
//   drupal_set_message($form_state['values']['trip_nid'].' - '.$form_state['values']['dest_lat']." : ".$form_state['values']['dest_lng']);
  global $user;
//   
  $node = new stdClass();
  $node->type = "destination";
// 
  $locs = get_locs_array();
  $loc_nid = $form_state['values']['location'];
  
// note: this is not the 'lid' 
  
  $node->title = $locs[$loc_nid];
  $node->created = time();
  
  $node->changed = $node->created;
// 
//     
//   //set field values
   	$node->language = LANGUAGE_NONE; 
    $node->uid = $user->uid;
  	$node->status = 1; //(1 or 0): published or not
  	$node->promote = 0; //(1 or 0): promoted to front page
  	$node->comment = 1; //2 = comments on, 1 = comments off
// 
   	$node->field_trip_number[$node->language][0]['value']  = $form_state['values']['model'];
   	$node->field_day_number[$node->language][0]['value']  = $form_state['values']['trip_day'];
// 
//   	    $location = array(
//           'lid' => NULL,
//           'name' => $form_state['values']['location_name'],
//           'street' => '123',
//           'additional' => '',
//           'city' => '',
//           'province' => '',
//           'postal_code' => 99999,
//           'country' => 'US',
//           'latitude' => (float) ($form_state['values']['dest_lat']),
//           'longitude' => (float) ($form_state['values']['dest_lng']),
//           'source' => LOCATION_LATLON_GEOCODED_APPROX,
//           'inhibit_geocode' => TRUE,
//         );
//         $settings = variable_get('location_settings_node_' . $node->type, array());
//         $location['location_settings'] = $settings;
//         $node->locations[] = $location;
//  
	node_object_prepare($node);   
  	$node = node_submit($node); // Prepare node for saving
  	node_save($node);
	drupal_set_message( "Node with nid " . $node->nid . " saved!\n");
   	$form_state['redirect']  = 'tripper/'.$form_state['values']['trip_day'].'/'.$form_state['values']['model'];
 }
 
 
 function get_locs_array() {
 
 		$query = db_select('node','n');
		$query->leftJoin('location_instance','li', 'n.nid = li.nid');
		$locs = $query
				->fields('n', array('nid','title'))
				->fields('li', array('lid'))
				->condition('n.type', 'location')
				->condition('n.status', 1)
				->addTag('node_access')
				->execute()
				->fetchAllKeyed();
		return $locs;
 
 }
// 
// 
// 
// function route($form, &$form_state) {
// 	$form['description'] = array(
// 		'#type' => 'markup',
// 		'#markup' => '<div id="map"></div>',	
// 	);	
// 	
// 	return $form;
// }