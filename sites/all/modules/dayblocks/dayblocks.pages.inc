<?php

function dayblocks_default_page($day = NULL, $trip = NULL) {

	    $build = array();



		//parent query
        $query = db_select('node', 'n');
        $query->leftJoin('uc_products', 'prod', 'n.nid = prod.nid');
        $query->leftJoin('field_revision_field_number_of_days', 'day_count', 'n.nid = day_count.entity_id');
//        $query->leftJoin('taxonomy_index','ti', 'n.nid = ti.nid');


		
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
//		dsm($trips);

		//destinations query


		$nids = dayblocks_query($trip, $day);

// 
//         $query = db_select('node', 'n')->extend('PagerDefault');
//         $query->leftJoin('field_data_field_trip_number', 'trip_number', 'n.nid = trip_number.entity_id');
//         $query->leftJoin('field_data_field_day_number', 'day_number', 'n.nid = day_number.entity_id');
// //        $query->leftJoin('taxonomy_index','ti', 'n.nid = ti.nid');
// 
// 		
// 
//         $nids = $query
//                 ->fields('n', array('nid', 'sticky', 'created'))
//                 ->condition('trip_number.field_trip_number_value', $trip)
//                 ->condition('day_number.field_day_number_value', $day)
//                 ->condition('n.type', 'destination')
//                 ->condition('n.status', 1)
//                 ->orderBy('n.sticky', 'DESC')
//                 ->orderBy('n.created', 'ASC')
//                 ->limit(100)
//                 ->addTag('node_access')
//                 ->execute()
//                 ->fetchCol();

        if (!empty($nids)) {
            $nodes = node_load_multiple($nids);
            $build += array('nodes' => array(
                    '#theme' => 'dayblocks_page',
                    '#nodes' => $nodes,
                    '#trip' => $trips,
                    )); //theme('portfolio_' . $default_portfolio, array('nodes' => $nodes));
            $build['pager'] = array(
                '#theme' => 'pager',
                '#weight' => 5,
            );
        } else {
            $nodes = NULL;
            $build += array('nodes' => array(
                    '#theme' => 'dayblocks_page',
                    '#nodes' => $nodes,
                    '#trip' => $trips,
                    )); //theme('portfolio_' . $default_portfolio, array('nodes' => $nodes));
        }

	    
	// to add static values... look into addExpression    
	// $query->addExpression(':my_val', 'start_date', array(':my_val' => $start_date));
	    
	    
	    
	    
	    
	    
		return    $build;
}

