//
// Created by xxzyjy on 2018/2/8.
//
#include "catch.hpp"
#include "viewer_file_derivable.h"

typedef struct {
  gchar *filename;
}ViewerFileDerivablePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(ViewerFileDerivable,viewer_file_derivable,G_TYPE_OBJECT)

static void viewer_file_derivable_class_init(ViewerFileDerivableClass *klass){
}
static void viewer_file_derivable_init(ViewerFileDerivable* self){
  ViewerFileDerivablePrivate* priv = (ViewerFileDerivablePrivate*)viewer_file_derivable_get_instance_private(self);
}
TEST_CASE("viewer_file_derivable","[GObject]"){

}


