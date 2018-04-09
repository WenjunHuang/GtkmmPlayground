//
// Created by xxzyjy on 2018/1/29.
//

#include "catch.hpp"
#include <gtkmm.h>

void buildUi(const Glib::RefPtr<Gtk::Application> &app) {
  auto mainWindow = new Gtk::ApplicationWindow(app);
  mainWindow->set_title("First GTK+ Program");
  mainWindow->set_border_width(10);
  mainWindow->set_position(Gtk::WindowPosition::WIN_POS_CENTER);
  mainWindow->set_default_size(350, 70);

  mainWindow->signal_delete_event().connect([&](GdkEventAny *event) -> bool {
    app->quit();
    return true;
  });

  auto button = Gtk::manage(new Gtk::Button("Click me!"));
  mainWindow->add(*button);
  mainWindow->show_all();


}

TEST_CASE("basic", "[gtkmm]") {
  auto application = Gtk::Application::create("com.github.basic", Gio::ApplicationFlags::APPLICATION_FLAGS_NONE);
  application->signal_startup().connect([&]() {
    buildUi(application);
  });
  application->run();
}