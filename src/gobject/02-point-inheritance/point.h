#pragma once

#include <glib-object.h>

#define PLAYGROUND_TYPE_POINT playground_point_get_type()

G_DECLARE_DERIVABLE_TYPE(PlaygroundPoint, playground_point, PLAYGROUND, POINT, GObject)

struct _PlaygroundPointClass {
  GObjectClass parent;
  void (*clear)(PlaygroundPoint* self);
  void (*print)(PlaygroundPoint* self);
};

void playground_point_clear(PlaygroundPoint* self);
void playground_point_print(PlaygroundPoint* self);
