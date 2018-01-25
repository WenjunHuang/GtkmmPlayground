//
// Created by xxzyjy on 2018/1/22.
//
#include "catch.hpp"
#include <gtk/gtk.h>
#include <gtkmm.h>
#include <TestFixture.h>

constexpr int NUM_NAMES = 4;
const gchar *names[] = {"Andrew", "joe", "Samantha", "Jonathan"};

static void destroy(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
}

TEST_CASE("boxes", "[gtk]") {
  gtk_init(nullptr, nullptr);
  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Boxes");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 200, -1);

  auto vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  for (auto i = 0; i < NUM_NAMES; i++) {
    auto button = gtk_button_new_with_label(names[i]);
    gtk_box_pack_end(GTK_BOX(vbox), button, true, true, 0);
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
                             G_CALLBACK(gtk_widget_destroy),
                             (gpointer) button);
  }
  gtk_container_add(GTK_CONTAINER(window), vbox);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), nullptr);
  gtk_widget_show_all(window);
  gtk_main();
}

TEST_CASE("panes", "[gtk]") {
  gtk_init(nullptr, nullptr);
  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Panes");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 225, 150);

  auto hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  auto button1 = gtk_button_new_with_label("Resize");
  auto button2 = gtk_button_new_with_label("Me!");
  g_signal_connect_swapped(G_OBJECT(button1),
                           "clicked",
                           G_CALLBACK(gtk_widget_destroy),
                           (gpointer) window);
  g_signal_connect_swapped(G_OBJECT(button2),
                           "clicked",
                           G_CALLBACK(gtk_widget_destroy),
                           (gpointer) window);
  gtk_paned_pack1(GTK_PANED(hpaned), button1, false, false);
  gtk_paned_add2(GTK_PANED(hpaned), button2);

  gtk_container_add(GTK_CONTAINER(window), hpaned);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), nullptr);
  gtk_widget_show_all(window);

  gtk_main();
}

TEST_CASE("fixed", "[gtk]") {
  gtk_init(nullptr, nullptr);
  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Fixed");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  auto fixed = gtk_fixed_new();
  auto button1 = gtk_button_new_with_label("Pixel by pixel...");
  auto button2 = gtk_button_new_with_label("you choose my fate.");

  g_signal_connect_swapped(G_OBJECT(button1),
                           "clicked",
                           G_CALLBACK(gtk_widget_destroy),
                           (gpointer) window);
  g_signal_connect_swapped(G_OBJECT(button2),
                           "clicked",
                           G_CALLBACK(gtk_widget_destroy),
                           (gpointer) window);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), nullptr);

  gtk_fixed_put(GTK_FIXED(fixed), button1, 0, 0);
  gtk_fixed_put(GTK_FIXED(fixed), button2, 20, 30);

  gtk_container_add(GTK_CONTAINER(window), fixed);
  gtk_widget_show_all(window);

  gtk_main();
}

TEST_CASE("expander", "[gtk]") {
  gtk_init(nullptr, nullptr);

  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Expander");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 200, 100);

  auto expander = gtk_expander_new_with_mnemonic("Click __Me for More!");
  auto label = gtk_label_new("Hide me or show me,\nthat is your choice.");
  gtk_container_add(GTK_CONTAINER(expander), label);
  gtk_expander_set_expanded(GTK_EXPANDER(expander), true);
  gtk_container_add(GTK_CONTAINER(window), expander);

  gtk_widget_show_all(window);
  gtk_main();
}

TEST_CASE("handleboxes", "[gtk]") {
  gtk_init(nullptr, nullptr);

  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Handle Box");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 200, 100);

}

gboolean pulse_progress(GtkProgressBar *progress) {
  static gint count = 0;
  gtk_progress_bar_pulse(progress);
  count++;
  return count < 100;
}

TEST_CASE("timeouts", "[gtk]") {
  gtk_init(nullptr, nullptr);
  auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Timeouts");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 200, -1);

  auto progress = gtk_progress_bar_new();
  gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress), 0.1);

  g_timeout_add(100,(GSourceFunc)pulse_progress,(gpointer)progress);
  gtk_container_add(GTK_CONTAINER(window),progress);
  gtk_widget_show_all(window);
  gtk_main();
}