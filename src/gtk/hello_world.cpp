//
// Created by xxzyjy on 2018/1/22.
//

#include "catch.hpp"
#include <gtk/gtk.h>

static void destroy(GtkWidget *window, GtkLabel *label) {
  gtk_main_quit();
}

static gboolean delete_event(GtkWidget *window,
                             GdkEvent *event,
                             gpointer data) {
  if (event->type == GDK_DELETE)
    return false;
  return true;
}

TEST_CASE("gtk_hello_world", "[gtk]") {
  gtk_init(nullptr, nullptr);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Hello World!");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 200, 100);

  GtkWidget *label = gtk_label_new("Hello World");
  gtk_label_set_selectable(GTK_LABEL(label), true);

  gtk_container_add(GTK_CONTAINER(window), label);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), (gpointer) label);
  g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event), nullptr);

  gtk_window_set_resizable(GTK_WINDOW(window), false);
  gtk_widget_show_all(window);

  gtk_main();
}

TEST_CASE("buttons", "[gtk]") {
  gtk_init(nullptr, nullptr);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Buttons");
  gtk_container_set_border_width(GTK_CONTAINER(window), 25);
  gtk_widget_set_size_request(window, 200, 100);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), nullptr);

  GtkWidget *button = gtk_button_new_with_mnemonic("_Close");
  gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);

  g_signal_connect_swapped(G_OBJECT(button), "clicked",
                           G_CALLBACK(gtk_widget_destroy),
                           (gpointer) window);
  gtk_container_add(GTK_CONTAINER(window), button);
  gtk_widget_show_all(window);

  gtk_main();
}

#define FIRST_NAME "黄"
#define LAST_NAME "文俊"

gboolean key_press_event(GtkWidget *window, GdkEventKey *event, GtkWidget *label) {
  const gchar *windowTitle = gtk_window_get_title(GTK_WINDOW(window));

  if (g_str_equal(windowTitle, FIRST_NAME)) {
    gtk_window_set_title(GTK_WINDOW(window), LAST_NAME);
    gtk_label_set_text(GTK_LABEL(label), FIRST_NAME);
  } else {
    gtk_window_set_title(GTK_WINDOW(window), FIRST_NAME);
    gtk_label_set_text(GTK_LABEL(label), LAST_NAME);
  }


  return false;
}

TEST_CASE("exercise_21", "[gtk]") {
  gtk_init(nullptr, nullptr);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *label = gtk_label_new(FIRST_NAME);

  gtk_window_set_title(GTK_WINDOW(window), LAST_NAME);
  gtk_widget_set_size_request(window, 300, 100);
  gtk_window_set_resizable(GTK_WINDOW(window), false);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), nullptr);
  g_signal_connect(G_OBJECT(window),
                   "key-press-event",
                   G_CALLBACK(key_press_event),
                   (gpointer) label);

  gtk_container_add(GTK_CONTAINER(window), label);

  gtk_widget_show_all(window);
  gtk_main();
}

bool ex22_key_press_event(GtkWidget *window,GdkEventKey *event,GtkWidget *label) {
  const gchar* title;
  g_object_get(G_OBJECT(window),"title",&title,nullptr);
  if (g_str_equal(title,FIRST_NAME)) {
    g_object_set(G_OBJECT(window),"title",LAST_NAME,nullptr);
    g_object_set(G_OBJECT(label),"label",FIRST_NAME,nullptr);
  }else {
    g_object_set(G_OBJECT(window),"title",FIRST_NAME,nullptr);
    g_object_set(G_OBJECT(label),"label",LAST_NAME,nullptr);
  }
  return false;
}

TEST_CASE("exercise_2_2", "[gtk]") {
  gtk_init(nullptr, nullptr);
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_object_set(G_OBJECT(window), "title", LAST_NAME,
               "width-request", 300,
               "height-request", 100,
               nullptr);

  GtkWidget *label = gtk_label_new(nullptr);
  g_object_set(G_OBJECT(label), "label", FIRST_NAME, nullptr);

  gtk_container_add(GTK_CONTAINER(window), label);

  g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(destroy),nullptr);
  g_signal_connect(G_OBJECT(window),"key-press-event",G_CALLBACK(ex22_key_press_event),(gpointer)label);

  gtk_widget_show_all(window);
  gtk_main();
}