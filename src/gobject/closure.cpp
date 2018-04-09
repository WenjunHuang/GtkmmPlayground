//
// Created by xxzyjy on 2018/2/9.
//

#include <glib-object.h>
#include <iostream>
#include "catch.hpp"

extern "C" {
void call_back(gpointer user_data) {
  std::cout << "called"<<std::endl;
}
}

TEST_CASE("closure", "[GObject]") {
  auto c = g_cclosure_new(G_CALLBACK(call_back), nullptr, nullptr);
  g_closure_set_marshal(c,g_cclosure_marshal_VOID__VOID);

  GValue a = G_VALUE_INIT;
  g_value_init(&a,G_TYPE_POINTER);
  g_value_set_pointer(&a,nullptr);
  g_closure_invoke(c,
                   nullptr,
                   1,
                   &a,
                   nullptr);
}

