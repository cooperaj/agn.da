#pragma once
#include <pebble.h>

typedef struct ClaySettings {
  char Event_ID[6];
} __attribute__((__packed__)) ClaySettings;

static bool loadSettings();
static void saveSettings();
static void inboxReceivedHandler(DictionaryIterator *iter, void *context);
static void init();
static void deinit();