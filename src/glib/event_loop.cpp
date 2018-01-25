//
// Created by xxzyjy on 2018/1/24.
//

#include <glib.h>
#include "catch.hpp"

TEST_CASE("create_new_loop","[glib]"){
  GMainLoop *loop = g_main_loop_new(nullptr,true);
  REQUIRE(g_main_loop_is_running(loop) == true);
  g_main_loop_run(loop);
}