#pragma once

#include <glib-object.h>

G_BEGIN_DECLS
#define VIEWER_TYPE_FILE viewer_file_get_type()
G_DECLARE_FINAL_TYPE(ViewerFile,viewer_file,VIEWER,FILE,GObject)

ViewerFile *viewer_file_new();

G_END_DECLS
