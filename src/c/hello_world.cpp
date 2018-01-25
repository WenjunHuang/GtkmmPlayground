//
// Created by rick on 2018/1/22.
//
#include <catch.hpp>
#include <gtk/gtk.h>

void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

gboolean delete_event(GtkWidget* widget,GdkEvent* event,gpointer data){
    return false;
}

TEST_CASE("hello_world_gtk", "[gtk]") {
    gtk_init(nullptr, nullptr);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hello World!");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 100);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(destroy), nullptr);
    g_signal_connect(G_OBJECT(window), "delete_event",
                     G_CALLBACK(delete_event), nullptr);

    GtkWidget *label = gtk_label_new("Hello World");
    gtk_label_set_selectable(GTK_LABEL(label),true);

    gtk_container_add(GTK_CONTAINER(window),label);
    gtk_widget_show_all(window);

    gtk_main();

}

