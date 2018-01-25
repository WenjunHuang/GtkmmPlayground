//
// Created by rick on 2018/1/24.
//
#include "catch.hpp"
#include "BuildApplication.h"

template<typename T, size_t N>
size_t size_of_array(T (&a)[N]) {
  return N;
};

TEST_CASE("build_app", "[gtkmm]") {
  Glib::setenv("GSETTINGS_SCHEMA_DIR","/Users/xxzyjy/Source/GtkmmPlayground/src/buildapp",false);
  auto application = BuildApplication::create();
  char *files[] = {"buidapp", "/Users/xxzyjy/Source/GtkmmPlayground/src/buildapp/window.glade","/Users/xxzyjy/Source/GtkmmPlayground/src/glade/derived.glade"};
  application->run(size_of_array(files), files);
}
