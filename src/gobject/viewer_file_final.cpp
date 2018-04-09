//
// Created by xxzyjy on 2018/2/6.
//
#include <gio/gio.h>
#include "catch.hpp"
#include "viewer_file_final.h"

/* Private structure definition. */
struct _ViewerFile {
  GObject parent_instance;
  gchar *filename;
  guint zoom_level;

  GInputStream *input_stream;
};

G_DEFINE_TYPE(ViewerFile, viewer_file, G_TYPE_OBJECT)

enum {
  PROP_FILENAME = 1,
  PROP_ZOOM_LEVEL,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES];

static void viewer_file_set_property(GObject *object,
                                     guint property_id,
                                     const GValue *value,
                                     GParamSpec *pspec) {
  ViewerFile *self = VIEWER_FILE(object);
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

static void viewer_file_get_property(GObject *object,
                                     guint property_id,
                                     GValue *value,
                                     GParamSpec *pspec) {
  ViewerFile *self = VIEWER_FILE(object);
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

static void viewer_file_dispose(GObject *gobject) {
  ViewerFile *self = VIEWER_FILE(gobject);
  g_clear_object(&self->input_stream);

  G_OBJECT_CLASS(viewer_file_parent_class)->dispose(gobject);
}

static void viewer_file_finalize(GObject *gobject){
  ViewerFile *self = VIEWER_FILE(gobject);

  g_free(self->filename);

  G_OBJECT_CLASS(viewer_file_parent_class)->finalize(gobject);
}

static void viewer_file_class_init(ViewerFileClass *klass) {
  GObjectClass *object_class = G_OBJECT_CLASS(klass);
  object_class->set_property = viewer_file_set_property;
  object_class->get_property = viewer_file_get_property;
  object_class->dispose = viewer_file_dispose;
  object_class->finalize = viewer_file_finalize;

  obj_properties[PROP_FILENAME] =
    g_param_spec_string("filename",
                        "Filename",
                        "Name of the file to load and display from.",
                        nullptr,
                        (GParamFlags) (G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE));
  obj_properties[PROP_ZOOM_LEVEL] =
    g_param_spec_uint("zoom-level",
                      "Zoom level",
                      "Zoom level to view the file at.",
                      0,
                      10,
                      2,
                      G_PARAM_READWRITE);
  g_object_class_install_properties(object_class,
                                    N_PROPERTIES,
                                    obj_properties);
}

static void viewer_file_init(ViewerFile *instance) {

}

TEST_CASE("viewer_file", "[GObject]") {
  auto obj1 = g_object_new(VIEWER_TYPE_FILE, "filename", "~/some file.txt", nullptr);
  gchar *filename;
  guint zoom_level;

  g_object_get(obj1, "filename", &filename, "zoom-level", &zoom_level, nullptr);

}
