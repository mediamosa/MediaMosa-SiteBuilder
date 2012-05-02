
(function ($) {
  Drupal.color = {
    logoChanged: false,
    callback: function(context, settings, form, farb, height, width) {
      // Change the logo to be the real one.
      if (!this.logoChanged) {
        $('#preview #preview-logo img').attr('src', Drupal.settings.color.logo);
        this.logoChanged = true;
      }
      // Remove the logo if the setting is toggled off. 
      if (Drupal.settings.color.logo == null) {
        $('div').remove('#preview-logo');
      }
      
      // Header background
      $('#preview #preview-header', form).css('background-color', $('#palette input[name="palette[header_bg]"]', form).val());
      
      // Slogan background
      $('#preview #preview-slogan', form).css('background-color', $('#palette input[name="palette[sloganbar]"]', form).val());
      
      // Slogan text
      $('#preview #preview-slogan h1', form).css('color', $('#palette input[name="palette[slogantext]"]', form).val());
      
      // UI background
      $('#preview #preview-featured', form).css('background-color', $('#palette input[name="palette[box]"]', form).val());

      // Video Hover Effect
      $('#preview #preview-video-overlay', form).css('background-color', $('#palette input[name="palette[videohover]"]', form).val());

      // Links
      $('#preview a', form).css('color', $('#palette input[name="palette[link]"]', form).val());
      
      // Primary Text
      $('#preview p', form).css('color', $('#palette input[name="palette[primary_text]"]', form).val());

      // Secondary Text
      $('#preview .preview-created', form).css('color', $('#palette input[name="palette[secondary_text]"]', form).val());

      // Tertiary Text
      $('#preview .preview-views-count', form).css('color', $('#palette input[name="palette[tertiary_text]"]', form).val());
  
    }
  };
})(jQuery);
