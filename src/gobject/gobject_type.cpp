//
// Created by rick on 2018/1/22.
//

#include "catch.hpp"
#include <glib-object.h>

TEST_CASE("value", "[gobject]") {
  GValue a_value = G_VALUE_INIT;
  GValue b_value = G_VALUE_INIT;
  guint64 a, b;

  a = 0xdeadbeef;

  g_value_init(&a_value, G_TYPE_UINT64);
  g_value_set_uint64(&a_value, a);

  g_value_init(&b_value, G_TYPE_UINT64);
  g_value_copy(&a_value, &b_value);

  b = g_value_get_uint64(&b_value);

  REQUIRE(a == b);
}

TEST_CASE("test_objecT", "[gobject]") {
  GObject *obj;
  GValue obj_vala = G_VALUE_INIT;
  GValue obj_valb = G_VALUE_INIT;
//  obj =g_object_new(VIEWER_TYPE_FILE,nullptr);

}