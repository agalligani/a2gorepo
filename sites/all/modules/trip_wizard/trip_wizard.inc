<?php


/**
 * The primary formbuilder function for the wizard form. 
 */


function form_example_wizard($form, &$form_state) {

  // Initialize a description of the steps for the wizard.
  if (empty($form_state['step'])) {
    $form_state['step'] = 1;
    $form_state['step_information'] = _form_example_steps();
  }
  $step = &$form_state['step'];
  drupal_set_title(t('Trip Wizard: Step @step', array('@step' => $step)));

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form = $form_state['step_information'][$step]['form']($form, $form_state);

  // Show the 'previous' button if appropriate.
  if ($step > 1) {
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#name' => 'prev',
      '#submit' => array('form_example_wizard_previous_submit'),
      '#limit_validation_errors' => array(),
    );
  }

  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information'])) {
    // The Next button should be included on every step
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#name' => 'next',
      '#submit' => array('form_example_wizard_next_submit'),
    );
  }
  else {
    // Just in case there are no more steps, we use the default submit handler
    // of the form wizard.
    $form['finish'] = array(
      '#type' => 'submit',
      '#value' => t('Create trip'),
    );
  }

  // Include each validation function defined for the different steps.
  if (function_exists($form_state['step_information'][$step]['form'] . '_validate')) {
    $form['next']['#validate'] = array($form_state['step_information'][$step]['form'] . '_validate');
  }

  return $form;
}

/**
 * Submit handler for the "previous" button.
 */
 
function form_example_wizard_previous_submit($form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
  if ($current_step > 1) {
    $current_step--;
    $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
  }
 $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the 'next' button.
 *
 * @param $form
 * @param $form_state
 *
 * @ingroup form_example
 */
function form_example_wizard_next_submit($form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];

  if ($current_step < count($form_state['step_information'])) {
    $current_step++;
    if (!empty($form_state['step_information'][$current_step]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
    else {
      $form_state['values'] = array();
    }
    $form_state['rebuild'] = TRUE;  // Force rebuild with next step.
    return;
  }
}

function _form_example_steps() {
  return array(
      1 => array(
        'form' => 'form_wizard_start_location',
      ),
      2 => array(
        'form' => 'form_wizard_trip_type',
      ),
      3 => array(
        'form' => 'form_wizard_enter_custom_dates',
      ),
      
      4 => array(
        'form' => 'form_wizard_custom_trip',
      ),
    );
}

/**
 * Returns form elements for the 'personal info' page of the wizard.
 *
 * @ingroup form_example
 */

function form_wizard_start_location($form, &$form_state) {

  $form = array();
  
//  Airstream2Go
// 	123 N. 10th Street,
// 	Las Vegas, NV
  $result = db_query('select tid, name from taxonomy_term_data where vid in (select vid from taxonomy_vocabulary where name = \'Base\')');
 
 	foreach ($result as $base) {
		$options[$base->tid] = $base->name; 		
	}	
//  $options = array('1' => 'Las Vegas, NV', '2' => 'Los Angeles, CA');
  
  $form['page1_text'] = array(
  	'#type' => 'markup',
  	'#markup' => '<p><h3>Airstream2Go now has 2 locations, Las Vegas and Los Angeles. To begin your journey please the location where you would like to pick-up your Airstream.</h3></p>',
  );
  
  $form['start_location'] = array(
  	'#type' => 'radios',
  	'#title' => 'Start/End location',
  	'#description' => 'Choose the originating location.',
  	'#options' => $options,
  	'#required' => TRUE,
//    '#default_value' => !empty($form_state['values']['start_location']) ? $form_state['values']['start_location'] : '1',
  );
  
  
  return $form;
}

/**
 * @ingroup form_example
 */

function form_wizard_trip_type($form, &$form_state) {
// select product nids from 
	$result = db_query('select tid, vid, name, description, weight from taxonomy_term_data where tid in (select ti2.tid from taxonomy_index as ti2 where ti2.nid in (select n.nid from node as n where nid in (select ti.nid from taxonomy_index as ti where ti.tid = :location) and ti2.tid in (select tid from taxonomy_term_data where vid in '.
		'(select vid from taxonomy_vocabulary where name = \'Package Type\'))))', array('location' => $form_state['step_information'][1]['stored_values']['start_location']));

	$options = array();


	foreach($result as $package_type) {
	$options = array($package_type->tid => $package_type->name);
	
	}
	
// 	$result = db_query('select uc.vid, uc.nid, n.title, uc.model, uc.list_price, uc.cost, uc.sell_price from {uc_products} as uc, {node} as n where n.nid = uc.nid');
// 	foreach ($result as $node) {
// 		$options[$node->nid] = $node->title; 		
// 	}	
$result = db_query('select tid, vid, name, description from taxonomy_term_data where vid in (select vid from taxonomy_vocabulary where name = \'Base\') and tid = :tid', array('tid'=>	$start_loc = $form_state['step_information'][1]['stored_values']['start_location']));
foreach($result as $loc) {
	$loc_desc = $loc->name;
}
	$start_loc = $form_state['step_information'][1]['stored_values']['start_location'];
	$cust_option = $loc_desc." Customized Trip Plan ";
	$options['CUSTOM_'.$form_state['step_information'][1]['stored_values']['start_location']] = $cust_option;
	
  $form = array();
  
  $form['page1_text'] = array(
  	'#type' => 'markup',
  		'#markup' => '<p><h3>We offer many pre-packaged adventure trip options originating from our '.$loc_desc.' location. Choose a trip option type to see what we have to offer, or select "'.$cust_option.'" and go off on your own.</h3></p>',
  );
  
  
	
  $form['triptype'] = array(
    '#type' => 'radios',
    '#title' => t('Available Trip Types <span class="form-required" title="This field is required.">*</span>'),
    '#description' => t('Pick one of the trip plans for '.$loc_desc.' described above.'),
    '#options' => $options,
//    '#required' => TRUE,
//    '#default_value' => !empty($form_state['values']['city']) ? $form_state['values']['city'] : '',

  );
  
    $form['tripcustom'] = array(
    '#type' => 'hidden',
    '#value' => 'CUSTOM_'.$form_state['step_information'][1]['stored_values']['start_location'],
  );

  return $form;
}

/**
 */
function form_wizard_trip_type_validate($form, &$form_state) {
   if ($form_state['values']['triptype'] == NULL) {
     form_set_error('triptype', t('You must select a trip type before continuing.'));
   }
}


/**
 */
// select uc.vid, uc.nid, n.title, uc.model, uc.list_price, uc.cost, uc.sell_price from uc_products as uc, node as n where n.nid = uc.nid and uc.nid in (select nid from taxonomy_index where tid = '31');


function form_wizard_enter_custom_dates($form, &$form_state) {

	$start_loc = $form_state['step_information'][1]['stored_values']['start_location'];
	$trip_type = $form_state['step_information'][2]['stored_values']['triptype'];
	$trip_cust = $form_state['step_information'][2]['stored_values']['tripcustom'];


  $form = array();


if(!($trip_type==$trip_cust)) {
	drupal_goto('trip_wizard_prepackage/'.$start_loc.'/'.$trip_type);
} else {

  $loc_desc = get_location($form_state['step_information'][1]['stored_values']['start_location']);
	
	// set-up start date default (change this later perhaps...)
	 $today_date = date('Y-m-d H:M:S');
 	 $format = 'm/d/Y';  



	  $form['text_1'] = array(
     		'#type' => 'markup',
     		'#markup' => '<div><h3>Great! Let\'s check on vehicle availability for your custom trip starting from '.$loc_desc.'.</h3></div>',
   			);
   			
	  $form['text_2'] = array(
     		'#type' => 'markup',
     		'#markup' => '<div><h4>What date would you like to pick up your Airstream from Airstream2Go '.$loc_desc.'?</h4></div>',
   			);

  //set up 
  
  $form['start_date'] = array(
	'#type' => 'date_popup',
  	'#title' => 'Trip Start Date',
  	'#description' => 'Choose the the date you are planning to begin your adventure.',
  	'#date_label_position' => 'within',
  	'#date_format' => $format, 
  	'#required' => TRUE,
  	'#datepicker_options' => array(),
  	'#default_value' => !empty($form_state['values']['start_date']) ? $form_state['values']['start_date'] : $today_date,
  );

  $form['text_3'] = array(
     		'#type' => 'markup',
     		'#markup' => '<div><h4>What date would you like to return your Airstream to Airstream2Go '.$loc_desc.'?</h4></div><br/>'.
     		'<i>&raquo;Return date MUST be at least five (5) days beyond the Start Date.</i>',
   			);
  
  $form['end_date'] = array(
	'#type' => 'date_popup',
  	'#title' => 'Trip End Date',
  	'#description' => 'Choose the the date you are planning to return from your adventure.',
  	'#date_label_position' => 'within',
  	'#date_format' => $format, 
  	'#required' => TRUE,
  	'#datepicker_options' => array(),
  	'#default_value' => !empty($form_state['values']['end_date']) ? $form_state['values']['end_date'] : $today_date,
  );
  	
  $form['text_1'] = array(
     		'#type' => 'markup',
     		'#markup' => '<div>'.$form_state['step_information'][2]['stored_values']['triptype'].'</div>',
   			);

	}
	  
  return $form;
}

function form_wizard_enter_custom_dates_validate($form, &$form_state) {
   if ($form_state['values']['start_date'] == NULL) {
     form_set_error('start_date', t('You must select a start date before continuing.'));
   }
   
   if ($form_state['values']['end_date'] == NULL) {
     form_set_error('end_date', t('You must select an end date before continuing.'));
   }
   
  if ((!($form_state['values']['start_date'] == NULL)) && (!($form_state['values']['end_date'] == NULL))) {
  		if(count_days(strtotime($form_state['values']['start_date']),strtotime($form_state['values']['end_date']))<5) {
		     form_set_error('end_date', t('End date must be at least five days after start date.'));
   		}
	}
}


//The

function form_wizard_custom_trip($form, &$form_state) {
	$form = array();
	
		$start_date = strtotime($form_state['step_information'][3]['stored_values']['start_date']);
		$end_date = strtotime($form_state['step_information'][3]['stored_values']['start_date']);
		$format = ('m/d/Y');
  // determine start location string
  
  $loc_desc = get_location($form_state['step_information'][1]['stored_values']['start_location']);

	  $options = array('23'=>'"Little Rig" - Airstream 23\' International Model','28'=>'"Big Rig" - Airstream 28\' International Model',);
	  
	  $form['text_1'] = array(
     		'#type' => 'markup',
     		'#markup' => '<div><h3>You are in luck!</h3><h4>Airstream2GO shows 2 Airstreams available from '.date($format, $start_date).' to '.date($format, $end_date).' at our '.$loc_desc.' location.</h4></div><br/>',
     		);
     		
  
  	 $form['model'] = array(
     		'#type' => 'radios',
     		'#options' => $options,
  	 	);


	  $form['text_2'] = array(
     		'#type' => 'markup',
     		'#markup' => '<div><h4>Please indicate which of these luxurious Airstream models you would prefer to take along on your trip.</h4></div><br/>'
     		);

	  $form['text_2'] = array(
     		'#type' => 'markup',
     		'#markup' => '<br/><div><h4>Each rental includes the use of a GMC Yukon tow vehicle with a \'GM Onstar\' navigational system.</h4></div><br/>'
     		);
		
	
	return $form;	


}


/**
 * Wizard form submit handler.
 * - Saves away $form_state['values']
 *
 * @param $form
 * @param $form_state
 *
 * @ingroup form_example
 */


function form_example_wizard_submit($form, &$form_state) {
   
   global $user;
   
//   $node = new stdClass();
//   $node->type = 'product';
//   
//   node_object_prepare($node);
//   
//   $node->title = 'new product test';
//   $node->language = LANGUAGE_NONE;
//   
//   $body_text = 'Trip Package';
//   
////   	print $form_state['step_information'][1]['stored_values']['start_location'];
//   	$start_date = strtotime($form_state['step_information'][3]['stored_values']['start_date']);
//   	$end_date	= strtotime($form_state['step_information'][3]['stored_values']['end_date']);

   
   drupal_set_message(print_r($form_state['step_information'][1]['stored_values']));
//   
//   $node->body[$node->language][0]['value'] = $body_text;
//   $node->body[$node->language][0]['summary'] = text_summary($body_text);
//   $node->body[$node->language][0]['format'] = 'full_html';
//   $node->body[$node->language][0]['field_start_date'] = $start_date;
//   $node->body[$node->language][0]['field_end_date'] = $end_date;
//   $node->body[$node->language][0]['field_number_of_days'] = count_days($start_date, $end_date);
//   
//      $path = 'content/programmatically_created_node_' . date('YmdHis');
//   $node->path = array('alias' => $path);
   
//   $path = 'content/'.$user->uid.'/
//  node_save($node);
//   dsm($node);
    
  
}





function count_days( $a, $b )
{
// First we need to break these dates into their constituent parts:
	$gd_a = getdate( $a );
	$gd_b = getdate( $b );
 
	// Now recreate these timestamps, based upon noon on each day
	// The specific time doesn't matter but it must be the same each day
	$a_new = mktime( 12, 0, 0, $gd_a['mon'], $gd_a['mday'], $gd_a['year'] );
	$b_new = mktime( 12, 0, 0, $gd_b['mon'], $gd_b['mday'], $gd_b['year'] );
 
	// Subtract these two numbers and divide by the number of seconds in a
	// day. Round the result since crossing over a daylight savings time
	// barrier will cause this time to be off by an hour or two.
	return round( abs( $a_new - $b_new ) / 86400 );
}


function get_location($tid = NULL) {
$result = db_query('select tid, vid, name, description from {taxonomy_term_data} where vid in (select vid from {taxonomy_vocabulary} where name = \'Base\') and tid = :tid', array('tid'=>	$tid));
	foreach($result as $loc) {
		$loc_desc = $loc->name;
	}
	return $loc_desc;
}
