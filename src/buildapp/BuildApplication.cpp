//
// Created by rick on 2018/1/24.
//

#include <iostream>
#include "BuildApplication.h"
#include "AppPrefs.h"

BuildApplication::BuildApplication() :
  Gtk::Application("org.gtkmm.examples.application", Gio::APPLICATION_HANDLES_OPEN) {

}

Glib::RefPtr<BuildApplication> BuildApplication::create() {
  return Glib::RefPtr<BuildApplication>(new BuildApplication);
}

MainWindow *BuildApplication::create_appwindow() {
  auto appwindow = MainWindow::create();
  add_window(*appwindow);
  appwindow->signal_hide().connect(sigc::bind<Gtk::Window *>(
    sigc::mem_fun(*this, &BuildApplication::on_hide_window), appwindow
  ));
  return appwindow;
}

void BuildApplication::on_activate() {
  try {
    auto appwindow = create_appwindow();
    appwindow->present();
  } catch (const std::exception &ex) {
    std::cerr << "BuildApplication::on_activate(): " << ex.what() << std::endl;
  }
}

void BuildApplication::on_open(const Gio::Application::type_vec_files &files, const Glib::ustring &hint) {
  MainWindow *appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<MainWindow *>(windows[0]);

  try {
    if (!appwindow)
      appwindow = create_appwindow();

    for (const auto &file: files)
      appwindow->open_file_view(file);

    appwindow->present();
  } catch (const std::exception &ex) {
    std::cerr << "BuildApplication::on_open(): " << ex.what() << std::endl;
  }
}

void BuildApplication::on_hide_window(Gtk::Window *window) {
  delete window;
}

void BuildApplication::on_startup() {
  Gtk::Application::on_startup();

  add_action("preferences", sigc::mem_fun(*this, &BuildApplication::on_action_preferences));
  add_action("quit", sigc::mem_fun(*this, &BuildApplication::on_action_quit));
  set_accel_for_action("app.quit", "<Ctrl>Q");

  auto refBuilder = Gtk::Builder::create();
  refBuilder->add_from_resource("/org/gtkmm/exampleapp/app_menu.glade");

  auto object = refBuilder->get_object("appmenu");
  auto app_menu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(object);
  set_app_menu(app_menu);

}

void BuildApplication::on_action_preferences() {
  auto prefs_dialog = AppPrefs::create(*get_active_window());
  prefs_dialog->present();
  prefs_dialog->signal_hide().connect(sigc::bind<Gtk::Window *>(sigc::mem_fun(*this,
                                                                              &BuildApplication::on_hide_window),
                                                                prefs_dialog));

}

void BuildApplication::on_action_quit() {
  auto windows = get_windows();
  for (auto window:windows)
    window->hide();
  quit();

}
