(function ($, win) {

Drupal.behaviors.hideSubmitBlockit = {
  attach: function(context) {
    var timeoutId = null;
      $("#mediamosa-sb-asset-upload-form").once('hideSubmitButton', function () {
      var $form = $(this);

      // Bind to form submit.
      $("#mediamosa-sb-asset-upload-form").submit(function (e) {
        var $inp;
	// Check for file.
        file_upload = $('input.form-file', $form).val();
	if (!file_upload) {
	  alert('You must provide a file.');
          return false;
        }

        if (!e.isPropagationStopped()) {
            $('input.form-submit', $form).attr('disabled', 'disabled').each(function (i) {
              var $button = $(this);
              $button.addClass('hide-submit-disable');
              $inp = $button;
            });
        }
        return true;
      });
    });
  }
};

})(jQuery, window);

