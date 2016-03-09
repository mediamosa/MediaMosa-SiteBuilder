/**
 * @file
 */
jQuery(document).ready(function() {

  function reloadPage() {
    // refresh this page.
    location.reload();
  }

  function getProgress() {
    jQuery.ajax({
      url: "/sb/mediamosa_job/jobprogress/" + mediamosa_sb_job_id,
      success: function (msg) {
        if (msg.message == 'waiting') {
          msg.percentage = 10;
          jQuery(".stillprogress-label").text('waiting for queue..');
        }
        else if (msg.message == 'inprogress') {
          jQuery(".stillprogress-label").text('in progress..');
          msg.percentage = 30;
        }
        else {
          jQuery(".stillprogress-label").text(msg.message);
        }
        jQuery("#stillprogressbar").progressbar("value", msg.percentage);
        if ((msg.percentage == 100) || !(mediamosa_sb_job_id > 0)) {
          setTimeout(reloadPage, 1000);
        }
        else {
          setTimeout(getProgress, 3000);
        }
      },
      error: function(msg) {
        setTimeout(reloadPage, 3000);
      }
    });
  }

  var progressbar = jQuery("#stillprogressbar"),
  progressLabel = jQuery(".stillprogress-label");
  progressbar.progressbar({
      value: false,
      change: function() {
      },
      complete: function() {
        progressLabel.text("Complete!");
      }
  });
  setTimeout(getProgress, 1000);
});
