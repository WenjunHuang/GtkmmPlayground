//
// Created by xxzyjy on 2018/1/19.
//

#include "catch.hpp"
#include <gstreamermm.h>
#include <iostream>

typedef enum {
  GST_PLAY_FLAG_VIDEO = (1 << 0), /* We want video output */
  GST_PLAY_FLAG_AUDIO = (1 << 1), /* We want audio output */
  GST_PLAY_FLAG_TEXT = (1 << 2)  /* We want subtitle output */
} GstPlayFlags;

TEST_CASE("gstmm_basic", "[gst]") {
  Gst::init();
  auto pipeline = Gst::Parse::launch("playbin uri=file:///Users/xxzyjy/Desktop/gravity.mpg");

//  gint flags = pipeline->get_flags();
//  flags |= GST_PLAY_FLAG_VIDEO | GST_PLAY_FLAG_AUDIO;
//  flags &= ~GST_PLAY_FLAG_TEXT;
//  pipeline->set_property("flags",flags);

  /* Set connection speed. This will affect some internal decisions of playbin */
  pipeline->set_property("connection-speed", 56);
  pipeline->set_state(Gst::State::STATE_PLAYING);

  auto bus = pipeline->get_bus();
  auto msg = bus->pop(Gst::CLOCK_DONE, Gst::MESSAGE_ERROR);

  if (msg) {
    std::cerr << "Error" << std::endl;
  } else {
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(main_loop);
  }

}