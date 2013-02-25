<?php

function packages_def_page($type = NULL) {


    global $user;

	$default_portfolio = '3c';

//    $default_portfolio = $type;
//     if (empty($type)) {
//         $default_portfolio = theme_get_setting('default_portfolio', 'finesse');
//     }
	
	


    $portfolio_type_arr = array('4c', '3c', '2c', '1c');
    
    $build = array();


    if (in_array($default_portfolio, $portfolio_type_arr)) {


        $query = db_select('node', 'n')->extend('PagerDefault');
        if(arg(1)) {
        $query->leftJoin('taxonomy_index','ti', 'n.nid = ti.nid');
        $query->condition('ti.tid', arg(1));
        }
        $nids = $query
                ->fields('n', array('nid', 'sticky', 'created'))
                ->condition('type', 'product')
                ->condition('status', 1)
                ->orderBy('sticky', 'DESC')
                ->orderBy('created', 'DESC')
                ->limit(3)
                ->addTag('node_access')
                ->execute()
                ->fetchCol();

        if (!empty($nids)) {
            $nodes = node_load_multiple($nids);
            $build += array('nodes' => array(
                    '#theme' => 'packages_' . $default_portfolio,
                    '#nodes' => $nodes,
                    )); //theme('portfolio_' . $default_portfolio, array('nodes' => $nodes));
            $build['pager'] = array(
                '#theme' => 'pager',
                '#weight' => 5,
            );
        } else {
            drupal_set_message(t('No packages available.'));
        }
    } else {

        drupal_set_message(t('No packages available.'));
    }

    return $build;
}