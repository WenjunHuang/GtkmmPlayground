#pragma once

#include <glib-object.h>

G_BEGIN_DECLS
#define MEDIA_TYPE_CLEANABLE media_cleanable_get_type()

G_DECLARE_INTERFACE(MediaCleanable,media_cleanable, MEDIA, CLEANABLE, GObject)
struct _MediaCleanableInterface {
  GTypeInterface parent_interface;

  void (*clean)(MediaCleanable *self);
};

void media_cleanable_clean(MediaCleanable *self);
G_END_DECLS



