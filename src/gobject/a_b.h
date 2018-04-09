#pragma once
#include <glib-object.h>

typedef struct {
  GTypeInstance parent;
  int field_a;
  int field_b;
}A;

typedef struct {
  GTypeClass parent_class;
  void (*method_a)();
  void (*method_b)();
}AClass;

typedef struct {
  A parent;
  int field_c;
  int field_d;
}B;

typedef struct {
  AClass parent_class;
  void (*method_c)();
  void (*method_d)();
}BClass;