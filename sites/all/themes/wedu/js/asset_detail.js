(function ($) {
  // Store our function as a property of Drupal.behaviors.
  Drupal.behaviors.mediamosa_dc_qdc = {
    attach: function (context, settings) {

      var metadata_dc = $('#tab-metadata-dc h2');
      var metadata_qdc = $('#tab-metadata-qdc h2');

      /* Hide empty fields by default */
      var tabsdc = $('#tab-metadata-dc .empty');
      tabsdc.hide();
      var tabsqdc = $('#tab-metadata-qdc .empty');
      tabsqdc.hide();

      metadata_dc.find('a').click(function(event){
        tabsdc.toggle('slow');
      });
      metadata_qdc.find('a').click(function(event){
        tabsqdc.toggle('slow');
      });
    }
  };

}(jQuery));
