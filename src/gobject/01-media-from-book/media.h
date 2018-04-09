#pragma once
#include <glib-object.h>
#include "cleanable.h"

#define MEDIA_TYPE_MEDIA media_media_get_type()

G_DECLARE_FINAL_TYPE(MediaMedia, media_media, MEDIA, MEDIA, GObject)

void media_media_unpack(MediaMedia* self);
void media_media_throw_out(MediaMedia* self,gboolean permanent);