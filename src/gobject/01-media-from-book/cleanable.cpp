//
// Created by xxzyjy on 2018/2/9.
//

#include "cleanable.h"

G_DEFINE_INTERFACE(MediaCleanable, media_cleanable, G_TYPE_OBJECT)

static guint cleanable_base_init_count = 0;

static void media_cleanable_default_init(MediaCleanableInterface *klass) {
  cleanable_base_init_count++;
}

void media_cleanable_clean(MediaCleanable *self) {
  g_return_if_fail(MEDIA_IS_CLEANABLE(self));
  g_object_ref(self);
  MEDIA_CLEANABLE_GET_IFACE(self)->clean(self);
  g_object_unref(self);
}