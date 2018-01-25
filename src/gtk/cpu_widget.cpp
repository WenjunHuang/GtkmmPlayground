//
// Created by xxzyjy on 2018/1/24.
//

#include <gtk/gtk.h>

/* Standard Gobject macros */
#define MY_TYPE_CPU (my_cpu_get_type())
#define MY_CPU(obj) (G_TYPE_CHECK_INSTANCE_CASE((obj),MY_TYPE_CPU,MyCpu))
#define MY_CPU_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass),MY_TYPE_CPU,MyCpuClass))
#define MY_IS_CPU(obj)(G_TYPE_CHECK_INSTANCE_TYPE((obj),MY_TYPE_CPU))
#define MY_IS_CPU_CLASS(klass)(G_TYPE_CHECK_CLASS_TYPE((klass),MY_TYPE_CPU))
#define MY_CPU_GET_CLASS(obj)(G_TYPE_INSTANCE_GET_CLASS((obj),MY_TYPE_CPU,MyCpuClass))

/* Type definition */
typedef struct _MyCpu MyCpu;
typedef struct _MyCpuClass MyCpuClass;
typedef struct _MyCpuPrivate MyCpuPrivate;

struct _MyCpu {
  GtkWidget parent;
  MyCpuPrivate *priv;
};
struct _MyCpuClass {
  GtkWidgetClass parent_class;
};

/*Public API*/
GType my_cpu_get_type() G_GNUC_CONST;
GtkWidget *my_cpu_new();
gdouble my_cpu_get_percent(MyCpu *cpu);
void my_cpu_set_percent(MyCpu *cpu,gdouble sel);

/* properties enum */
enum {
  P_0,
  P_PERCENT
};

struct _MyCpuPrivate {
  gdouble percent;
  GdkWindow *window;
};

const gint WIDTH = 80;
const gint HEIGHT = 100;

/* Define type */
//G_DEFINE_TYPE(MyCpu,my_cpu,GTK_TYPE_WIDGET)