const CONF_VERSION = "v1.";

var app_config = require("./config");

function save_configuration(config) {
    var db = localStorage;
    for (var config_item in config) {
        var old_access_token = db.getItem(CONF_VERSION + config_item);
        if (old_access_token != config[config_item]) {
            if (config[config_item] == null) {
                db.removeItem(CONF_VERSION + config_item);
            } else {
                db.setItem(CONF_VERSION + config_item, config[config_item]);
            }

        }
    }
}

// When you click on Settings in Pebble's phone app. Go to the configuration.html page.
function show_configuration() {
    var db = localStorage;

    var json = JSON.stringify({
        "joind_in_api_key": app_config.joind_in_api_key,
        "access_token": db.getItem(CONF_VERSION + "access_token"),
        "event_id": db.getItem(CONF_VERSION + "event_id"),
        "show_all_talks": db.getItem(CONF_VERSION + "show_all_talks"),
        "error": db.getItem(CONF_VERSION + "error")
    });
    db.removeItem(CONF_VERSION + "error");

    Pebble.openURL(app_config.configuration_url + "#" + encodeURIComponent(json));
}

// When you click Save on the configuration.html page, receive the configuration response here.
function webview_closed(e) {
    var json = e.response;
    save_configuration(JSON.parse(decodeURIComponent(json)));

    // Send to the watchapp
    Pebble.sendAppMessage({ "SetupComplete": true }, function() {
        console.log('App configuration updated');
    }, function(e) {
        console.log('Error updating app configuration');
    });
}

// Setup the configuration events
Pebble.addEventListener("showConfiguration", show_configuration);
Pebble.addEventListener("webviewclosed", webview_closed);

Pebble.addEventListener('ready', function() {
    console.log('PebbleKit JS ready!');
});


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
