//
// Created by xxzyjy on 2018/1/19.
//

//#include <gstreamermm/element.h>
//#include <gstreamermm/init.h>
//#include <gstreamermm/bus.h>
//#include <gstreamermm.h>
#include <gst/gst.h>
//#include <gtkmm/main.h>
#include "catch.hpp"

//TEST_CASE("basic","[gst]"){
typedef enum {
  GST_PLAY_FLAG_VIDEO         = (1 << 0), /* We want video output */
  GST_PLAY_FLAG_AUDIO         = (1 << 1), /* We want audio output */
  GST_PLAY_FLAG_TEXT          = (1 << 2)  /* We want subtitle output */
} GstPlayFlags;
TEST_CASE("basic_1","[gstreamer]"){
  gint flags;

  /* Initialize GStreamer */
  gst_init(NULL,NULL);

  /* Build the pipeline */
  GstElement *player = gst_element_factory_make("playbin", "player");
  g_object_set(player, "uri", "file:///Users/xxzyjy/Desktop/gravity.mpg", NULL);
  g_object_get(player, "flags", &flags, NULL);
  flags |= GST_PLAY_FLAG_VIDEO | GST_PLAY_FLAG_AUDIO;
  flags &= ~GST_PLAY_FLAG_TEXT;
  g_object_set(player, "flags", flags, NULL);

  /* Set connection speed. This will affect some internal decisions of playbin */
  g_object_set(player, "connection-speed", 56, NULL);
  /* Start playing */
  gst_element_set_state(player, GST_STATE_PLAYING);

  /* Wait until error or EOS */
//  bus = gst_element_get_bus (pipeline);
//  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
  GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(main_loop);

  /* Free resources */
}
//
//int w_main(){
//  Gst::init();
//  auto main = Gtk::Main();
//  auto pipeline = Gst::Parse::launch("playbin uri=/Users/xxzyjy/Downloads/sintel.mkv");
//  pipeline->set_state(Gst::State::STATE_PLAYING);
//
//  auto bus  = pipeline->get_bus();
//  auto msg = bus->pop(Gst::CLOCK_TIME_NONE,Gst::MESSAGE_ERROR|Gst::MESSAGE_EOS);
//
//  pipeline->set_state(Gst::State::STATE_NULL);
//  main.run();
//
//}
