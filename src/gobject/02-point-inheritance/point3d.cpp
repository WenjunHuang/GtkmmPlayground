//
// Created by xxzyjy on 2018/2/9.
//

#include <iostream>
#include <boost/format.hpp>
#include "point3d.h"

struct _PlaygroundPoint3D {
  PlaygroundPoint parent_instance;
  gint z;
};

// properties
enum {
  PROP_Z,
  PROPS_COUNT
};
static GParamSpec *PROPS[PROPS_COUNT] = {nullptr,};

G_DEFINE_TYPE(PlaygroundPoint3D, playground_point3d, PLAYGROUND_TYPE_POINT)

static void playground_point3d_print_internal(PlaygroundPoint* point){
  PlaygroundPoint3D *self = PLAYGROUND_POINT3D(point);
  g_return_if_fail(self != nullptr);

//  std::cout << boost::format("")

}
static void playground_point3d_class_init(PlaygroundPoint3DClass *klass) {
  GObjectClass *object_class = G_OBJECT_CLASS(klass);

  // 注册属性
  PROPS[PROP_Z] = g_param_spec_int(
    "z",//name
    "z",
    "z location of point3d",
    INT_MIN,
    INT_MAX,
    0,
    (GParamFlags) (G_PARAM_READWRITE)
  );
  g_object_class_install_properties(object_class, PROPS_COUNT, &PROPS[0]);
}

static void playground_point3d_init(PlaygroundPoint3D *self) {}