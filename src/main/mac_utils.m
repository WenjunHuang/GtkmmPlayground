#include <gdk/gdkquartz.h>
void* get_nswindow(void *window) {
   return gdk_quartz_window_get_nsview(window);
}