//
// Created by xxzyjy on 2018/1/29.
//

#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include "catch.hpp"

TEST_CASE("gtk_window", "[cairo]") {
  Gtk::Main main;

  Gtk::Window mainWindow;
  auto window = &mainWindow;
  window->set_title("GTK window");
  window->set_size_request(420, 120);
  window->set_position(Gtk::WindowPosition::WIN_POS_CENTER);
  window->signal_delete_event().connect([](GdkEventAny* event){
    Gtk::Main::quit();
    return false;
  });

  auto darea = Gtk::manage(new Gtk::DrawingArea);
  darea->signal_draw().connect([](const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgb(0,0,0);
    cr->select_font_face("Sans",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_NORMAL);
    cr->set_font_size(40);
    cr->move_to(10,50);
    cr->show_text("Disziplin ist Macht.");
    return true;
  });

  window->add(*darea);
  window->show_all();

  main.run();
}
