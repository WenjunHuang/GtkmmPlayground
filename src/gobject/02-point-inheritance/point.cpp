//
// Created by xxzyjy on 2018/2/9.
//

#include <iostream>
#include <boost/format.hpp>
#include "point.h"

typedef struct {
  gint x;
  gint y;
} PlaygroundPointPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(PlaygroundPoint, playground_point, G_TYPE_OBJECT)

void playground_point_print(PlaygroundPoint *self) {
  PLAYGROUND_POINT_CLASS(self)->print(self);
}

static void playground_point_print_internal(PlaygroundPoint *self) {
  PlaygroundPointPrivate *priv = (PlaygroundPointPrivate *) playground_point_get_instance_private(self);
  std::cout << boost::format("PlaygroundPoint{x: %1%, y: %2%}") % priv->x % priv->y << std::endl;
}

static void playground_point_clear_internal(PlaygroundPoint *self) {
//  PlaygroundPointPrivate *priv = (PlaygroundPointPrivate *) playground_point_get_instance_private(self);
  g_object_set(self,"x",0,"y",0,nullptr);

}

// properties
enum {
  PROP_X = 0,
  PROP_Y,
  PROPS_COUNT
};
static GParamSpec *PROPERTIES[PROPS_COUNT] = {nullptr,};

// signals
enum {
  CLEAR,
  SIGNALS_COUNT
};
static guint SIGNALS[SIGNALS_COUNT] = {0};

static void playground_point_class_init(PlaygroundPointClass *klass) {
  GObjectClass *object_class = G_OBJECT_CLASS(klass);

  //注册属性
  PROPERTIES[PROP_X] = g_param_spec_int(
    "x",
    "x",
    "x location of point",
    INT_MIN,
    INT_MAX,
    0,
    G_PARAM_READWRITE
  );
  PROPERTIES[PROP_Y] = g_param_spec_int(
    "y",
    "y",
    "y location of point",
    INT_MIN,
    INT_MAX,
    0,
    G_PARAM_READWRITE
  );
  g_object_class_install_properties(object_class, PROPS_COUNT, &PROPERTIES[0]);

  // 注册信号
  SIGNALS[CLEAR] = g_signal_new(
    "clear", // signal_name
    PLAYGROUND_TYPE_POINT, // itype
    (GSignalFlags) (G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED),// signal_flags
    0, // class_offset
    nullptr, // accumulator
    nullptr, // accu_data
    g_cclosure_marshal_VOID__VOID, // c_marshaller
    G_TYPE_NONE, // return type
    0 // n_params
  );

  // 实例方法
  klass->print = playground_point_print_internal;
  klass->clear = playground_point_clear_internal;
}

// 实例构造函数
static void playground_point_init(PlaygroundPoint* self){
  // noop
}