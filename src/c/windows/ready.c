#include "ready.h"

static Window *s_main_window;
static TextLayer *s_body_layer, *s_title_layer;
static StatusBarLayer *s_status_bar;

static GBitmap *s_icon_bitmap;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_status_bar = status_bar_layer_create();
  int16_t width = layer_get_bounds(window_layer).size.w;
  GRect frame = GRect(0, 0, width, STATUS_BAR_LAYER_HEIGHT);
  layer_set_frame(status_bar_layer_get_layer(s_status_bar), frame);
  layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));

  const GEdgeInsets title_insets = {.top = STATUS_BAR_LAYER_HEIGHT};
  s_title_layer = text_layer_create(grect_inset(bounds, title_insets));
  text_layer_set_text(s_title_layer, DIALOG_READY_WINDOW_APP_NAME);
  text_layer_set_text_color(s_title_layer, GColorBlack);
  text_layer_set_background_color(s_title_layer, GColorClear);
  text_layer_set_text_alignment(s_title_layer, GTextAlignmentCenter);
  text_layer_set_font(s_title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(s_title_layer));

  GSize title_size = text_layer_get_content_size(s_title_layer);
  const GEdgeInsets body_insets = {
      .top = STATUS_BAR_LAYER_HEIGHT + title_size.h + 5,
      .left = 5,
      .right = 5,
      .bottom = 5
  };
  s_body_layer = text_layer_create(grect_inset(bounds, body_insets));
  text_layer_set_text(s_body_layer, DIALOG_READY_WINDOW_MESSAGE);
  text_layer_set_text_color(s_body_layer, GColorBlack);
  text_layer_set_background_color(s_body_layer, GColorClear);
  text_layer_set_font(s_body_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(s_body_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_title_layer);
  text_layer_destroy(s_body_layer);

  status_bar_layer_destroy(s_status_bar);

  window_destroy(window);
  s_main_window = NULL;
}

void dialog_ready_window_push() {
  if(!s_main_window) {
    s_main_window = window_create();
    window_set_background_color(s_main_window, PBL_IF_COLOR_ELSE(GColorPictonBlue, GColorWhite));
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload
    });
  }
  window_stack_push(s_main_window, true);
}
