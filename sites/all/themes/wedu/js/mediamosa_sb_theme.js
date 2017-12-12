// Using the closure to map jQuery to $. 
(function ($) {
  // Store our function as a property of Drupal.behaviors.
  Drupal.behaviors.mediamosa_tabs = {
    attach: function (context, settings) {
      var navigation = $('#asset-tabs li');

      /* remove the active state of the tabs if there are any */
      var tabs = $('.asset-technical-information .tab');
      tabs.hide();

      /* on page load, set first tab active and set the first content field on active */
      var defaultActive = $('#asset-tabs li:first').addClass('active');
      var defaultActiveContent = $('#asset-tabs li:first a').attr('name');
      $('#' + defaultActiveContent).show();

      navigation.find('a').click(function(event){
        event.preventDefault;
        tabs.hide();
        navigation.removeClass('active');
        var goto_tab = $(this).attr('name');
        $('#' + goto_tab).toggle();
        $(this).parent('li').addClass('active');
        goto_tab = '';
      })
    }
  };

  Drupal.behaviors.ie_nth_fix = {
      attach: function (context, settings) {
        if ($.browser.msie && $.browser.version <= 8) {
          $('.page-assets #page_content .views-row:nth-child(4n)').addClass('fourth-child');
        }
      }
  };

}(jQuery));