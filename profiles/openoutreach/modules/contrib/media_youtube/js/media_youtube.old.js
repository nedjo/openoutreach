// $Id: media_youtube.js,v 1.1.2.2 2009/11/26 12:46:55 aaron Exp $

/**
 *  @file
 *  JavaScript for the Media: YouTube module.
 *
 *  This will send a YouTube link or embed code back to the module,
 *  which will return an embedded clip and fill in the uri on the main form.
 */
(function ($) {

/**
 *  Send the link back to the module, and fill in elements w/ correct info.
 */
Drupal.behaviors.mediaYoutubeLink = {
  attach: function (context, settings) {
    var ytdb = [];
    $('.form-item-media-youtube-url input', context).once('mediaYoutubeLink', function () {
      var uri = this.value;
      if (!ytdb[uri]) {
        ytdb[uri] = new Drupal.YTDB(uri);
      }
      var input = $(this);
      new Drupal.mediaYoutubeBind(input, ytdb[uri]);
    });
  }
};

/**
 * An AutoComplete object.
 */
Drupal.mediaYoutubeBind = function (input, db) {
  var yt = this;
  this.input = input;
  this.db = db;
  this.parsing = false;
  $(this.input)
    .keyup(function () { yt.parseurl(this); })
    .blur(function () { yt.parseurl(this); });

};

Drupal.mediaYoutubeBind.prototype.parseurl = function (input) {
  input.delay = 500;
  // Initiate delayed parse.
  if (input.timer) {
    clearTimeout(input.timer);
  }
  if (input.value.length == 0) {
    return;
  }
  if (input.value == input.current_value) {
    return;
  }
  input.current_value = input.value;
  input.url = Drupal.settings.mediaYoutube.parse_url + '?parse=' + Drupal.encodePath(input.value);
  input.timer = setTimeout(function () {

    // Ajax GET request for autocompletion.
    $.ajax({
      type: 'GET',
      url: input.url,
      dataType: 'json',
      success: function (val) {
        if (val.status == 'ok') {
          $('input.media-file-uri').val(val.uri);
          $('.media-youtube-preview-markup').html(val.preview);
        }
        else {
          $('input.media-file-uri').val('');
        }
      },
      error: function (xmlhttp) {
        alert(Drupal.ajaxError(xmlhttp, input.url));
      }
    });
  }, input.delay);
}

/**
 * Handler for the "keyup" event.
 */
Drupal.mediaYoutubeBind.prototype.onkeyup = function (input, e) {
  if (!e) {
    e = window.event;
  }
  switch (e.keyCode) {
    case 16: // shift.
    case 17: // ctrl.
    case 18: // alt.
    case 20: // caps lock.
    case 33: // page up.
    case 34: // page down.
    case 35: // end.
    case 36: // home.
    case 37: // left arrow.
    case 38: // up arrow.
    case 39: // right arrow.
    case 40: // down arrow.
      return true;

    case 9:  // tab.
    case 13: // enter.
    case 27: // esc.
      this.hidePopup(e.keyCode);
      return true;

    default: // All other keys.
      if (input.value.length > 0)
        this.populatePopup();
      else
        this.hidePopup(e.keyCode);
      return true;
  }
};


/**
 * An AutoComplete DataBase object.
 */
Drupal.YTDB = function (uri) {
  this.uri = uri;
  this.delay = 300;
  this.cache = {};
};

/**
 * Performs a cached and delayed search.
 */
Drupal.YTDB.prototype.search = function (searchString) {
  var db = this;
  this.searchString = searchString;

  // See if this string needs to be searched for anyway.
  searchString = searchString.replace(/^\s+|\s+$/, '');
  if (searchString.length <= 0 ||
    searchString.charAt(searchString.length - 1) == ',') {
    return;
  }

  // See if this key has been searched for before.
  if (this.cache[searchString]) {
    return this.owner.found(this.cache[searchString]);
  }

  // Initiate delayed search.
  if (this.timer) {
    clearTimeout(this.timer);
  }
  this.timer = setTimeout(function () {
    db.owner.setStatus('begin');

    // Ajax GET request for autocompletion.
    $.ajax({
      type: 'GET',
      url: Drupal.settings.mediaYoutube.parse_url + '/' + Drupal.encodePath(searchString),
      dataType: 'json',
      success: function (matches) {
        if (typeof matches.status == 'undefined' || matches.status != 0) {
          db.cache[searchString] = matches;
          // Verify if these are still the matches the user wants to see.
          if (db.searchString == searchString) {
            db.owner.found(matches);
          }
          db.owner.setStatus('found');
        }
      },
      error: function (xmlhttp) {
        alert(Drupal.ajaxError(xmlhttp, db.uri));
      }
    });
  }, this.delay);
};

/**
 * Cancels the current autocomplete request.
 */
Drupal.YTDB.prototype.cancel = function () {
  if (this.owner) this.owner.setStatus('cancel');
  if (this.timer) clearTimeout(this.timer);
  this.searchString = '';
};

})(jQuery);
