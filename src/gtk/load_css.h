#pragma once

#include <gtk/gtk.h>

void app_set_theme(const gchar *theme_path) {
  g_assert(theme_path != nullptr);

  auto file = g_file_new_for_path(theme_path);
  if (file != nullptr) {
    auto screen = gdk_screen_get_default();
    auto provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, file, nullptr);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_reset_widgets(screen);
  }

}