//
// Created by xxzyjy on 2018/2/9.
//

#include "catch.hpp"
#include "media.h"

typedef struct _MediaMedia {
  GObject parent_instance;
  guint inv_nr;
  GString *location;
  GString *title;
  gboolean orig_package;
} MediaMedia;

// properties
enum {
  PROP_INV_NR = 1,
  PROP_ORIG_PACKAGE
};

// signals
enum {
  UNPACKED,
  THROW_OUT,
  LAST_SIGNAL
};

static guint media_signal[LAST_SIGNAL] = {0, 0};


static void media_media_cleanable_interface_init(MediaCleanableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(MediaMedia, media_media, G_TYPE_OBJECT,
                        G_IMPLEMENT_INTERFACE(MEDIA_TYPE_CLEANABLE,
                                              media_media_cleanable_interface_init))

static void media_media_set_property(GObject *object,
                                     guint prop_id,
                                     const GValue *value,
                                     GParamSpec *pspec) {
  MediaMedia *self = MEDIA_MEDIA(object);
  switch (prop_id) {
    case PROP_INV_NR: {
      guint new_inv_nr = g_value_get_uint(value);
      self->inv_nr = new_inv_nr;
      break;
    }
    case PROP_ORIG_PACKAGE: {
      gboolean new_orig_package = g_value_get_boolean(value);
      self->orig_package = new_orig_package;
      if (self->orig_package)
        g_signal_emit(self,media_signal[UNPACKED],0);
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

static void media_media_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec) {
  MediaMedia *self = MEDIA_MEDIA(object);

  switch (prop_id) {
    case PROP_INV_NR:
      g_value_set_uint(value, self->inv_nr);
      break;
    case PROP_ORIG_PACKAGE:
      g_value_set_boolean(value, self->orig_package);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

static void media_media_class_init(MediaMediaClass *klass) {
  GObjectClass *objectClass = G_OBJECT_CLASS(klass);
  objectClass->set_property = media_media_set_property;
  objectClass->get_property = media_media_get_property;

  // 定义属性
  auto inv_nr_param = g_param_spec_uint("inventory-id",
                                        "inventory number",
                                        "number on inventory label",
                                        0,
                                        UINT_MAX,
                                        0,
                                        G_PARAM_READWRITE);
  auto orig_package_param = g_param_spec_boolean("orig-package",
                                                 "original package?",
                                                 "is item in its original package?",
                                                 false,
                                                 G_PARAM_READWRITE);
  g_object_class_install_property(objectClass, PROP_INV_NR, inv_nr_param);
  g_object_class_install_property(objectClass, PROP_ORIG_PACKAGE, orig_package_param);

  // 定义信号
  media_signal[UNPACKED] = g_signal_new(
    "unpacked",// name
    MEDIA_TYPE_MEDIA, // class type identifier
    (GSignalFlags) (G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED),// options
    0,
    nullptr,
    nullptr,
    g_cclosure_marshal_VOID__VOID,
    G_TYPE_NONE,
    0);

  media_signal[THROW_OUT] = g_signal_new(
    "throw_out",
    MEDIA_TYPE_MEDIA,
    (GSignalFlags) (G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED),
    0,
    nullptr,
    nullptr,
    g_cclosure_marshal_VOID__BOOLEAN,
    G_TYPE_NONE,
    1,
    G_TYPE_BOOLEAN
  );
}

// MediaCleanable 接口实现
static void media_media_clean(MediaCleanable *self) {
  g_print("cleaning media.\n");
}

static void media_media_cleanable_interface_init(MediaCleanableInterface *iface) {
  iface->clean = media_media_clean;
}

// constructor
static void media_media_init(MediaMedia *self) {}


// media common functions
void media_media_unpacked(MediaMedia *self) {
  if (self->orig_package) {
    g_object_set(self, "orig-package", false, nullptr);
    g_print("Media unpacked.\n");
  } else {
    g_print("Media already unpacked.\n");
  }
}

void media_media_throw_out(MediaMedia *self, gboolean permanent) {
  if (permanent)
    g_print("Trashing media.\n");
  else
    g_print("Media not in the dumpster quite yet.\n");
}

static void meep_meep(MediaMedia *media) {
  guint nr;
  g_object_get(media, "inventory-id", &nr, nullptr);
  g_print("Meep-meep! (Inventory number: %d)\n", nr);
}

TEST_CASE("media", "[GObject]") {
  auto media = g_object_new(MEDIA_TYPE_MEDIA, "inventory-id", 42, "orig-package", false, nullptr);
  auto handler_id = g_signal_connect(media,
                                     "unpacked",
                                     G_CALLBACK(meep_meep),
                                     nullptr);

//  g_signal_emit_by_name(media, "unpacked");
//
//  g_print("Setting inventory-id=37, orig-package=true\n");
  g_object_set(media,
               "inventory-id", 37,
               "orig-package", true,
               nullptr);

  media_cleanable_clean(MEDIA_CLEANABLE(media));

  g_object_unref(media);
}