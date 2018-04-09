#pragma once

#include  <glib-object.h>

G_BEGIN_DECLS
#define VIEWER_TYPE_FILE_DERIVABLE viewer_file_derivable_get_type()
G_DECLARE_DERIVABLE_TYPE(ViewerFileDerivable, viewer_file_derivable, VIEWER, FILE_DERIVABLE, GObject)
struct _ViewerFileDerivableClass{
  GObjectClass parent_class;

  /* Class virtual function fields. */
  void (*open)(ViewerFileDerivable *file,GError **error);

  /* padding to allow adding up to 12 new virtual functions without breaking ABI. */
  gpointer padding[12];
};
G_END_DECLS