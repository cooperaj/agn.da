#pragma once
#include <pebble.h>

typedef struct AppSettings {
  uint8_t SetupComplete;
} __attribute__((__packed__)) AppSettings;

static bool loadSettings();
static void saveSettings();
static void inboxReceivedHandler(DictionaryIterator *iter, void *context);
static void init();
static void deinit();
