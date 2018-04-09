//
// Created by xxzyjy on 2018/2/7.
//

#include <iostream>
#include <boost/format.hpp>
#include <glib-object.h>
#include "catch.hpp"

G_BEGIN_DECLS
// interface definition
#define HACK_TYPE_FOOABLE hack_fooable_get_type()
typedef struct {
} HackFooable;
typedef struct {
  GTypeInterface parent;

  void (*foo)(HackFooable *self);
} HackFooableInterface;

static void hack_fooable_base_init(gpointer klass) {
  std::cout << "hack_fooable_base_init" << std::endl;
}

static void hack_fooable_interface_init(gpointer klass, gpointer data) {
  std::cout << "hack_fooable_class_init" << std::endl;
}
GType hack_fooable_get_type() {
  static volatile GType type = 0;
  if (g_once_init_enter(&type)) {
    const GTypeInfo info = {
      .class_size=sizeof(HackFooableInterface),
      .base_init=hack_fooable_base_init,
      .base_finalize=nullptr,
      .class_init=hack_fooable_interface_init,
      .class_data=nullptr,
      .class_finalize=nullptr,
      .instance_size=0,
      .instance_init=nullptr,
      .n_preallocs=0,
      .value_table=nullptr
    };
    GType newType = g_type_register_static(G_TYPE_INTERFACE, "HackFooable", &info, (GTypeFlags) 0);
    g_once_init_leave(&type, newType);
  }
  return type;
}

inline HackFooable *HACK_FOOABLE(gpointer ptr) {
  return G_TYPE_CHECK_INSTANCE_CAST(ptr, HACK_TYPE_FOOABLE, HackFooable);
}


inline gboolean HACK_IS_FOOABLE(gpointer ptr) {
  return G_TYPE_CHECK_INSTANCE_TYPE(ptr, HACK_TYPE_FOOABLE);
}

inline HackFooableInterface *HACK_FOOABLE_GET_IFACE(gpointer ptr) {
  return G_TYPE_INSTANCE_GET_INTERFACE(ptr, HACK_TYPE_FOOABLE, HackFooableInterface);
}

void hack_fooable_foo(HackFooable *self) {
  g_return_if_fail(HACK_IS_FOOABLE(self));
  HackFooableInterface *iface = HACK_FOOABLE_GET_IFACE(self);
  g_return_if_fail(iface->foo != nullptr);
  iface->foo(self);
}

// class HackBase definition

typedef struct {
  GObject parent;
} HackBase;
typedef struct {
  GObjectClass parent_class;
} HackBaseClass;

#define HACK_TYPE_BASE (hack_base_get_type())
GType hack_base_get_type();

static inline HackBase *HACK_BASE(gpointer ptr) {
  return G_TYPE_CHECK_INSTANCE_CAST(ptr, HACK_TYPE_BASE, HackBase);
}

static inline HackBaseClass *HACK_BASE_CLASS(gpointer klass) {
  return G_TYPE_CHECK_CLASS_CAST(klass, HACK_TYPE_BASE, HackBaseClass);
}

static inline gboolean HACK_IS_BASE(gpointer ptr) {
  return G_TYPE_CHECK_INSTANCE_TYPE(ptr, HACK_TYPE_BASE);
}

static inline gboolean HACK_IS_BASE_CLASS(gpointer klass) {
  return G_TYPE_CHECK_CLASS_TYPE(klass, HACK_TYPE_BASE);
}

static inline HackBaseClass *HACK_BASE_GET_CLASS(gpointer ptr) {
  return G_TYPE_INSTANCE_GET_CLASS(ptr, HACK_TYPE_BASE, HackBaseClass);
}

static void hack_base_constructed(GObject *obj) {
  std::cout << "hack_base_constructed" << std::endl;
  /* update the object state depending on constructor properties*/
  /* Always chain up to the parent constructed function to complete object initialization */

  // 这里获取的gobject_class
  auto me = HACK_BASE_GET_CLASS(obj);
  auto p1 = G_OBJECT_CLASS(me);
  // g_type_class_peek_parent只能在类初始化时调用
//  auto base = g_type_class_peek_parent(me);
//  auto gobject_class = G_OBJECT_CLASS(base);
//  gobject_class->constructed(obj);

  GObjectClass* parent = (GObjectClass*)g_type_class_peek_parent(me);

  auto ok_object = G_OBJECT_CLASS(g_type_class_peek(G_TYPE_OBJECT));
  ok_object->constructed(obj);
}

static void hack_base_base_init(gpointer klass) {
  std::cout << "hack_base_base_init " << klass << std::endl;
}

static void hack_base_base_finalize(gpointer klass) {
  std::cout << "hack_base_finalize " << klass << std::endl;
}

static void hack_base_class_init(gpointer klass, gpointer data) {
  std::cout << "hack_base_class_init " << klass << std::endl;
  GObjectClass *object_class = G_OBJECT_CLASS(klass);
  object_class->constructed = hack_base_constructed;

  auto parent = g_type_class_peek_parent(klass);
}

static void hack_base_class_finalize(gpointer klass, gpointer data) {
  std::cout << "hack_base_class_finalize " << klass << std::endl;
}

static void hack_base_instance_init(GTypeInstance *instance, gpointer klass) {
  std::cout << "hack_base_instance_init " << instance << std::endl;
}

//
GType hack_base_get_type() {
  static GType type = 0;
  if (type == 0) {
    const GTypeInfo info = {
      .class_size = sizeof(HackBaseClass),
      .base_init=hack_base_base_init,
      .base_finalize=hack_base_base_finalize,
      /* interface types, classed types, instantiated types */
      .class_init=hack_base_class_init,
      .class_finalize=nullptr,
      .class_data=nullptr,
      /* instantiated types */
      .instance_size=sizeof(HackBase),
      .n_preallocs=0,
      .instance_init=hack_base_instance_init,
      /* value handling */
      .value_table=nullptr

    };
    type = g_type_register_static(G_TYPE_OBJECT, "HackBase", &info, (GTypeFlags) 0);
  }
  return type;
}
//class HackDerived definition
typedef struct {
  HackBase parent;
  gchar *filename;
  guint zoom_level;
} HackDerived;
typedef struct {
  HackBaseClass parent_class;
} HackDerivedClass;

#define HACK_TYPE_DERIVED hack_derived_get_type()
GType hack_derived_get_type();

inline HackDerived *HACK_DERIVED(gpointer obj) {
  return G_TYPE_CHECK_INSTANCE_CAST(obj, HACK_TYPE_DERIVED, HackDerived);
}

inline HackDerivedClass *HACK_DERIVED_CLASS(gpointer klass) {
  return G_TYPE_CHECK_CLASS_CAST(klass, HACK_TYPE_DERIVED, HackDerivedClass);
}

inline gboolean HACK_IS_DERIVED(gpointer obj) {
  return G_TYPE_CHECK_INSTANCE_TYPE(obj, HACK_TYPE_DERIVED);
}

inline gboolean HACK_IS_DERIVED_CLASS(gpointer klass) {
  return G_TYPE_CHECK_CLASS_TYPE(klass, HACK_TYPE_DERIVED);
}

inline HackDerivedClass *HACK_DERIVED_GET_CLASS(gpointer ptr) {
  return G_TYPE_INSTANCE_GET_CLASS(ptr, HACK_TYPE_DERIVED, HackDerivedClass);
}


void hack_derived_constructed(GObject *obj) {
  std::cout << "hack_derived_constructed" << std::endl;
  GObjectClass *parent = G_OBJECT_CLASS(g_type_class_peek_parent(HACK_DERIVED_GET_CLASS(obj)));
  parent->constructed(obj);
}

void hack_derived_base_init(gpointer klass) {
  std::cout << "derived_base_init " << klass << std::endl;
}

void hack_derived_base_finalize(gpointer klass) {
  std::cout << "derived_base_finalize " << klass << std::endl;
}

GObject *hack_derived_constructor(GType type,
                                  guint n_construct_properties,
                                  GObjectConstructParam *construct_properties) {
  std::cout << "hack_derived_constructor" << std::endl;
  auto object_class = G_OBJECT_CLASS(g_type_class_peek(HACK_TYPE_BASE));
  return object_class->constructor(type, n_construct_properties, construct_properties);
}

enum {
  PROP_FILENAME = 1,
  PROP_ZOOM_LEVEL,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = {nullptr,};

static void hack_derived_set_property(GObject *object,
                                      guint property_id,
                                      const GValue *value,
                                      GParamSpec *pspec) {
  HackDerived *self = HACK_DERIVED(object);
  switch (property_id) {
    case PROP_FILENAME:
      g_free(self->filename);
      self->filename = g_value_dup_string(value);
      g_print("filename: %s\n", self->filename);
      break;
    case PROP_ZOOM_LEVEL:
      self->zoom_level = g_value_get_uint(value);
      g_print("zoom level: %u\n", self->zoom_level);
      break;
    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
      break;
  }
}

static void hack_derived_get_property(GObject *object,
                                      guint property_id,
                                      GValue *value,
                                      GParamSpec *pspec) {
  HackDerived *self = HACK_DERIVED(object);
  switch (property_id) {
    case PROP_FILENAME:
      g_value_set_string(value, self->filename);
      break;
    case PROP_ZOOM_LEVEL:
      g_value_set_uint(value, self->zoom_level);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
      break;
  }
}

void hack_derived_class_init(gpointer klass, gpointer data) {
  std::cout << "derived_class_init " << klass << std::endl;
  GObjectClass *object_class = G_OBJECT_CLASS(klass);
  object_class->constructed = hack_derived_constructed;
  object_class->constructor = hack_derived_constructor;
  object_class->set_property = hack_derived_set_property;
  object_class->get_property = hack_derived_get_property;

  obj_properties[PROP_FILENAME] =
    g_param_spec_string("filename",
                        "Filename",
                        "Name of the file to load and display from.",
                        nullptr,
                        (GParamFlags) (G_PARAM_READWRITE));
  obj_properties[PROP_ZOOM_LEVEL] =
    g_param_spec_uint("zoom-level",
                      "Zoom level",
                      "Zoom level to view the file at.",
                      0, //minimum value
                      100, // maximum value
                      2, // default value
                      G_PARAM_READWRITE);
  g_object_class_install_properties(object_class,
                                    N_PROPERTIES,
                                    obj_properties);
}

void hack_derived_instance_init(GTypeInstance *instance, gpointer klass) {
  std::cout << "derived_instance_init " << instance << std::endl;
}

void hack_derived_foo(HackFooable *self) {
  std::cout << "hack_derived_foo" << std::endl;
}
void hack_derived_fooable_interface_init(gpointer g_iface,
                                         gpointer iface_data) {
  HackFooableInterface *iface = static_cast<HackFooableInterface *>(g_iface);
  iface->foo = hack_derived_foo;
}

GType hack_derived_get_type() {
  static GType type = 0;
  if (type == 0) {
    const GTypeInfo info = {
      .class_size = sizeof(HackDerivedClass),
      .base_init = hack_derived_base_init,
      .base_finalize=hack_derived_base_finalize,
      .class_init=hack_derived_class_init,
      .class_finalize=nullptr,
      .class_data=nullptr,
      .instance_size=sizeof(HackDerived),
      .instance_init=hack_derived_instance_init,
      .n_preallocs=0,
      .value_table=nullptr
    };

    type = g_type_register_static(HACK_TYPE_BASE, "HackDerived", &info, (GTypeFlags) 0);

    // also implement interface HackFoo
    const GInterfaceInfo fooable_info = {
      .interface_data=nullptr,
      .interface_finalize=nullptr,
      .interface_init=hack_derived_fooable_interface_init
    };

    g_type_add_interface_static(HACK_TYPE_DERIVED, HACK_TYPE_FOOABLE, &fooable_info);
  }
  return type;
}

G_END_DECLS

TEST_CASE("hack_with_gtype_create", "[GType]") {
//  auto obj1 = g_type_create_instance(HACK_TYPE_BASE);
  auto obj2 = g_type_create_instance(HACK_TYPE_DERIVED);

//  g_type_free_instance(obj1);
  g_type_free_instance(obj2);

  std::cout << "------------------" << std::endl;
  auto obj3 = g_type_create_instance(HACK_TYPE_DERIVED);

  std::cout << "-------------------" << std::endl;
  hack_fooable_foo(HACK_FOOABLE(obj3));
  g_type_free_instance(obj3);
}

static void week_notify(gpointer data, GObject *where_the_object_was) {
  std::cout << "week_notify called" << std::endl;
}

TEST_CASE("hack_with_gobject_new", "[GObject]") {
  auto obj1 = g_object_new(HACK_TYPE_DERIVED, nullptr);

  // tedious way: g_object_set_property and g_object_get_property are meant to be used by language bindings.
//  GValue val = G_VALUE_INIT;
//  g_value_init(&val,G_TYPE_STRING);
//  g_value_set_string(&val,"hello world");
//  g_object_set_property(G_OBJECT(obj1),"filename",&val);
//  g_value_unset(&val);
//
//  g_value_init(&val,G_TYPE_UINT);
//  g_value_set_uint(&val,11);
//  g_object_set_property(G_OBJECT(obj1),"zoom-level",&val);
//  g_value_unset(&val);
  g_object_set(G_OBJECT(obj1), "zoom-level", 6, "filename", "~/some-file.txt", nullptr);

  guint zoomLevel;
  gchar *filename;
  g_object_get(G_OBJECT(obj1), "zoom-level", &zoomLevel,
               "filename", &filename, nullptr);
  std::cout << boost::format("zoomlevel: %1%, filename: %2%") % zoomLevel % filename << std::endl;
  g_free(filename);


  std::cout << "-------------------" << std::endl;
  auto obj2 = g_object_new(HACK_TYPE_DERIVED, nullptr);

  g_object_weak_ref(G_OBJECT(obj2), week_notify, nullptr);
  g_object_unref(obj2);
//  g_object_unref(obj1);
}
