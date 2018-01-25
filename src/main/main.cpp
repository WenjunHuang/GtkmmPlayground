//
// Created by xxzyjy on 2018/1/14.
//
#define CATCH_CONFIG_RUNNER

#include <gtkmm/application.h>
#include <gstreamermm/init.h>
#include <gtkmm/main.h>
#include "catch.hpp"

Glib::RefPtr<Gtk::Application> app;

//int main(int argc, char *argv[]) {
//  app = Gtk::Application::create("org.gtkmm.example");
//  int result = Catch::Session().run(argc, argv);
//  return (result < 0xff ? result : 0xff);
//}

int main(int argc,char *argv[]){

  int result = Catch::Session().run(argc, argv);
  return (result < 0xff ? result : 0xff);
}
