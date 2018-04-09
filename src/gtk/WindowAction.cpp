//
// Created by xxzyjy on 2018/2/12.
//
#define GTKMM_DISABLE_DEPRECATED
#include "catch.hpp"
#include <iostream>
#include <gtkmm.h>

void activate(Glib::RefPtr<Gtk::Application> app) {
  Gtk::ApplicationWindow *window = new Gtk::ApplicationWindow(app);
  window->set_title("Window Action");

  auto action = Gio::SimpleAction::create("save");
  action->signal_activate().connect([](auto var) {
    std::cout << "Hello Action" << std::endl;
  });
  window->add_action(action);

  auto button = Gtk::manage(new Gtk::Button);
  button->set_label("Save");
  gtk_actionable_set_action_name(GTK_ACTIONABLE(button->gobj()),"win.save");
  window->add(*button);

  window->show_all();
}

TEST_CASE("window_action", "[Gtkmm]") {
  auto app = Gtk::Application::create("org.github.wenjun.WindowAction", Gio::APPLICATION_HANDLES_OPEN);
  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(activate), app));
  app->run();
}
