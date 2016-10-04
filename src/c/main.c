#include <pebble.h>
#include "main.h"
#include "windows/setup.h"

// A struct for our specific settings (see main.h)
ClaySettings settings;

static bool loadSettings() {
  // Read settings from persistent storage, if they exist
  persist_read_data(1, &settings, sizeof(settings));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Load settings: Event_ID: %s", settings.Event_ID);
  
  return false;
}

static void saveSettings() {
  persist_write_data(1, &settings, sizeof(settings));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Save settings: Event_ID: %s", settings.Event_ID);
}

static void inboxReceivedHandler(DictionaryIterator *iter, void *context) {
  // Read event id
  Tuple *event_id = dict_find(iter, MESSAGE_KEY_Event_ID);
  if (event_id) {
    memcpy(settings.Event_ID, event_id->value->cstring, event_id->length);
  }
  
  saveSettings();
}

static void init() {
  // Open AppMessage connection
  app_message_register_inbox_received(inboxReceivedHandler);
  app_message_open(128, 128);
  
  if (loadSettings()) {
    // dialog_ready_window_push();
  } else {
    dialog_setup_window_push();
  }
}

static void deinit() {
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}