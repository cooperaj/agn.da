var app_config = require("./config");

// When you click on Settings in Pebble's phone app. Go to the configuration.html page.
function show_configuration() {
    var db = window.localStorage;

    var json = JSON.stringify({
        "joind_in_api_key": app_config.joind_in_api_key,
        "access_token": db.getItem("access_token"),
        "error": db.getItem("error")
    });
    db.removeItem("error");

    Pebble.openURL(app_config.configuration_url + "#" + encodeURIComponent(json));
}

// When you click Save on the configuration.html page, receive the configuration response here.
function webview_closed(e) {
    var json = e.response;
    var config = JSON.parse(json);

    var access_token = config.access_token;

    var db = window.localStorage;
    var old_access_token = db.getItem("access_token");
    if (old_access_token != access_token) {
        db.setItem("access_token", access_token);
    }

    //resolve_tokens(access_token);
}

// Setup the configuration events
Pebble.addEventListener("showConfiguration", show_configuration);
Pebble.addEventListener("webviewclosed", webview_closed);

/*Pebble.timelineSubscribe('all', function() {
  console.log('Subscribed to all');
}, function(err) {
  console.log('Error subscribing to topic: ' + err);
});

Pebble.timelineSubscribe('event_' + clay.Event_ID, function() {
  console.log('Subscribed to all');
}, function(err) {
  console.log('Error subscribing to topic: ' + err);
});*/
