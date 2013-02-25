jQuery.noConflict();

jQuery(document).ready(function($){



	init();


	var form_address = $('#edit-location-name');	
		form_address.val();
		default_text = $('#get-geo').html();
		
		
		
	$('#get-geo').click(function() {	
		$(this).html(default_text);	 
		var geo_url = 'http://maps.googleapis.com/maps/api/geocode/json?address='+form_address.val()+'&sensor=true'


		$.getJSON(geo_url, function(data) {

			if(data['status'] == 'OK') {
				 showLocs(data['results']);
				} else {
					$('#get-geo').append('<span> >> Location not found. Try again.</span>');
				}
			}); //end getJSON		
			return false;
		});  // end click
		
		
		function showLocs(locs) { 
				clear_form_options();			 			
				$('form#location-options').fadeIn();
				$('#edit-submit').fadeIn();
				$('#loc-map').fadeIn(3000);
		

				var radios = [];
 				var labels = [];
				for( var i = 0; i<locs.length; i++) {				
					radios[i]  = $('<input id="edit-loc-radios-'+i+
					'" class="form-radio" type="radio" checked="checked" value="'+i+'" name="loc_radios">');
					radios[i].data('address',locs[i]['formatted_address']);
					radios[i].data('lat',locs[i]['geometry']['location']['lat']);
					radios[i].data('lng',locs[i]['geometry']['location']['lng']);
					radios[i].data('nelat',locs[i]['geometry']['viewport']['northeast']['lat']);
					radios[i].data('nelng',locs[i]['geometry']['viewport']['northeast']['lng']);
					radios[i].data('swlat',locs[i]['geometry']['viewport']['southwest']['lat']);
					radios[i].data('swlng',locs[i]['geometry']['viewport']['southwest']['lng']);
					
 					labels[i]  = $('<label class="option" for="edit-loc-radios-'+i+'">'+locs[i]['formatted_address']+'</label><br/>');					
 						$(".form-item-loc-radios").append(radios[i]);
						$(".form-item-loc-radios").append(labels[i]);
						radios[i].click(
							function(e) {
									$('#get-geo').html(default_text+'>>'+' lat:'+$(this).data('lat')+' lng:'+$(this).data('lng'));
												 $('[name="dest_lat"]').val($(this).data('lat'));
												 $('[name="dest_lng"]').val($(this).data('lng'));			
												 $('#edit-location-name').val($(this).data('address')); 			
												makeMap($(this).data('lat'), $(this).data('lng'));
							});
					}
					// Turn the first option "on" by default
									$('#get-geo').html(default_text+'>>'+' lat:'+radios[0].data('lat')+' lng:'+radios[0].data('lng'));
									makeMap(radios[0].data('lat'), radios[0].data('lng'));
												
												 $('[name="dest_lng"]').val(radios[i].data('lng'));
												 $('[name="dest_lat"]').val(radios[i].data('lat'));
												 $('#edit-location-name').val(radios[i].data('address')); 			
		}

	
	
	function init() {
	
	//	clear_form_options();
	
// 				$('#edit-submit').hide();
		        $('#loc-map').hide();
		
$('form#trip-planner').after('<form id="location-options">'+		
	'	<div class="form-item form-type-radios form-item-loc-radios">'+ 
	'	<label for="edit-loc-radios">Choose a Location </label>'+
	'	<div id="edit-loc-radios" class="form-radios">'+
	'	<div class="description">Select option to see map of choice.</div>'+
	'	<div class="form-item form-type-radio form-item-loc-radios">'+
	'	</div>'+
	'	</div>'+
	'	</div>'+
	'	</form>');
	
	

		}
		
 	function clear_form_options() {
//  			$('#edit-submit').hide(); 			 			
 			$("#location-options radio").remove();
 			$("#location-options label.option").remove();
 			$('form#location-options').hide();		
 		}		
		
		
}); //end jQuery


    function makeMap(lat, lng) {
		var mapOptions = {
  		center: new google.maps.LatLng(lat, lng),
  				zoom: 8,
  				mapTypeId: google.maps.MapTypeId.ROADMAP
			};    
			
		var map = new google.maps.Map(document.getElementById("loc-map"), mapOptions);	
}	


// for future reference: the JSON for geocoding

// {
//   "types":["locality","political"],
//   "formatted_address":"Winnetka, IL, USA",
//   "address_components":[{
//     "long_name":"Winnetka",
//     "short_name":"Winnetka",
//     "types":["locality","political"]
//   },{
//     "long_name":"Illinois",
//     "short_name":"IL",
//     "types":["administrative_area_level_1","political"]
//   },{
//     "long_name":"United States",
//     "short_name":"US",
//     "types":["country","political"]
//   }],
//   "geometry":{
//     "location":[ -87.7417070, 42.1083080],
//     "location_type":"APPROXIMATE"
//   }
// }
// 



 

