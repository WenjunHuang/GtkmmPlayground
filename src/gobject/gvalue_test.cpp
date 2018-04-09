//
// Created by xxzyjy on 2018/2/9.
//


#include <glib-object.h>
#include "catch.hpp"

static void int2string(const GValue *src_value,GValue *dest_value){
  if (g_value_get_int(src_value)==42)
    g_value_set_static_string(dest_value,"An important number");
  else
    g_value_set_static_string(dest_value,"What's that?");
}

TEST_CASE("int_string","[GObject]"){
  GValue a = G_VALUE_INIT;
  GValue b = G_VALUE_INIT;
  const gchar *message;

  // gvalue starts empty
  REQUIRE_FALSE(G_VALUE_HOLDS_STRING(&a));

  // put a string in it
  g_value_init(&a,G_TYPE_STRING);
  REQUIRE(G_VALUE_HOLDS_STRING(&a));

  g_value_set_static_string(&a,"Hello, world!");
  g_print("%s\n",g_value_get_string(&a));

  // reset it to its pristine state
  g_value_unset(&a);

  // it can then be reused for another type
  g_value_init(&a,G_TYPE_INT);
  g_value_set_int(&a,42);

  // attempt to transform it into a GValue of type STRING
  g_value_init(&b,G_TYPE_STRING);

  // an int is transformable to a STRING
  REQUIRE(g_value_type_transformable(G_TYPE_INT,G_TYPE_STRING));

  g_value_transform(&a,&b);
  g_print("%s\n",g_value_get_string(&b));

  // attempt to transform it again using a custom transform function
  g_value_register_transform_func(G_TYPE_INT,G_TYPE_STRING,int2string);
  g_value_transform(&a,&b);
  g_print("%s\n",g_value_get_string(&b));

}