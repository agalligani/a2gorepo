/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*	Browser Compatibility Check
 /* ---------------------------------------------------------------------- */

(function ($) {
  
  if ( $.browser.msie ) {
    if(parseInt($.browser.version, 10) <= 7){
        window.location.href = "update-browser.html";
    }
}

  
})(jQuery);

