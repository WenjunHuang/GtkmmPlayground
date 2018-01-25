//
// Created by xxzyjy on 2018/1/23.
//

#include <glib-object.h>

enum{
  PROP_FILENAME = 1,
  PROP_ZOOM_LEVEL,
  N_PROPERTIES
};

constexpr GParamSpec *obj_properties[N_PROPERTIES] = {nullptr,};

