//
// Created by xxzyjy on 2018/1/23.
//

#include <gtk/gtk.h>
#include "catch.hpp"
#include "load_css.h"

TEST_CASE("scrolled_windows", "[gtk]") {
  gtk_init(nullptr, nullptr);
  app_set_theme("src/css/style.css");


  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Scrolled windows  & Viewports");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 500, 400);

  g_signal_connect(G_OBJECT(window),
                   "destroy",
                   G_CALLBACK(gtk_main_quit), nullptr);

  auto grid1 = gtk_grid_new();
  auto grid2 = gtk_grid_new();

  gtk_grid_set_row_spacing(GTK_GRID(grid1), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid1), 5);
  gtk_grid_set_row_spacing(GTK_GRID(grid2), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid2), 5);

  GtkWidget *buttons1[10][10], *buttons2[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      buttons1[i][j] = gtk_button_new_with_label("Close");
      auto image = gtk_image_new_from_icon_name("window-close", GTK_ICON_SIZE_BUTTON);
      gtk_button_set_always_show_image(GTK_BUTTON(buttons1[i][j]), true);
      gtk_button_set_image(GTK_BUTTON(buttons1[i][j]), image);
      gtk_button_set_relief(GTK_BUTTON(buttons1[i][j]), GTK_RELIEF_NONE);

      buttons2[i][j] = gtk_button_new_from_icon_name("window-close", GTK_ICON_SIZE_BUTTON);
      gtk_button_set_label(GTK_BUTTON(buttons2[i][j]), "Close");
      gtk_button_set_relief(GTK_BUTTON(buttons2[i][j]), GTK_RELIEF_NONE);

      gtk_grid_attach(GTK_GRID(grid1), buttons1[i][j], i, j, 1, 1);
      gtk_grid_attach(GTK_GRID(grid2), buttons2[i][j], i, j, 1, 1);
    }
  }

  auto swin = gtk_scrolled_window_new(nullptr, nullptr);
  gtk_scrolled_window_set_placement(GTK_SCROLLED_WINDOW(swin), GTK_CORNER_BOTTOM_LEFT);
  gtk_widget_set_size_request(GTK_WIDGET(swin), 100, 100);
  auto horizontal = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(swin));
  auto vertical = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(swin));
  auto viewport = gtk_viewport_new(horizontal, vertical);

  gtk_container_set_border_width(GTK_CONTAINER(swin), 5);
  gtk_container_set_border_width(GTK_CONTAINER(viewport), 5);

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swin),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(swin), grid1);
  gtk_container_add(GTK_CONTAINER(viewport), grid2);

  auto vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), viewport, true, true, 0);
  gtk_box_pack_start(GTK_BOX(vbox), swin, true, true, 0);

  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show_all(window);

  gtk_main();

}

TEST_CASE("textview", "[gtk]") {
  gtk_init(nullptr, nullptr);
  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(GTK_WIDGET(window), 250, 250);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), nullptr);
  auto textview = gtk_text_view_new();
  auto buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
  gtk_text_buffer_set_text(buffer, "Your 1st GtkTextView widget!", -1);

  auto scrolled = gtk_scrolled_window_new(nullptr, nullptr);
  gtk_container_add(GTK_CONTAINER(scrolled), textview);
  gtk_container_add(GTK_CONTAINER(window), scrolled);
  gtk_widget_show_all(window);

  gtk_main();
}

TEST_CASE("textview2", "[gtk]") {
  gtk_init(nullptr, nullptr);
  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(GTK_WIDGET(window), 250, 250);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), nullptr);

  auto font = pango_font_description_from_string("Monospace Bold 20");
  auto textview = gtk_text_view_new();
  gtk_widget_override_font(GTK_WIDGET(textview), font);
  gtk_text_view_set_pixels_above_lines(GTK_TEXT_VIEW(textview), 5);
  auto buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
  gtk_text_buffer_set_text(buffer, "Your 1st GtkTextView widget!", -1);

  auto scrolled = gtk_scrolled_window_new(nullptr, nullptr);
  gtk_container_add(GTK_CONTAINER(scrolled), textview);
  gtk_container_add(GTK_CONTAINER(window), scrolled);
  gtk_widget_show_all(window);

  gtk_main();
}