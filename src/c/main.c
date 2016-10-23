#include <pebble.h>
#include "main.h"
#include "windows/setup.h"
#include "windows/ready.h"

// A struct for our specific settings (see main.h)
AppSettings settings;

static bool loadSettings() {
  // Read settings from persistent storage, if they exist
  persist_read_data(1, &settings, sizeof(settings));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Load settings: SetupComplete: %s", settings.SetupComplete ? "true" : "false");

  return settings.SetupComplete;
}

static void saveSettings() {
  persist_write_data(1, &settings, sizeof(settings));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Save settings: SetupComplete: %s", settings.SetupComplete ? "true" : "false");
}

static void inboxReceivedHandler(DictionaryIterator *iter, void *context) {
  // Read event id
  Tuple *setup_complete = dict_find(iter, MESSAGE_KEY_SetupComplete);
  if (setup_complete) {
      settings.SetupComplete = setup_complete->value->uint8;
  }

  saveSettings();
}

static void init() {
  // Open AppMessage connection
  app_message_register_inbox_received(inboxReceivedHandler);
  app_message_open(128, 128);

  if (loadSettings()) {
    dialog_ready_window_push();
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
