//
// Created by xxzyjy on 2018/1/19.
//

#include <gstreamermm.h>
#include "catch.hpp"

struct CustomData {
  Glib::RefPtr<Gst::PlayBin> playbin;
  bool playing;
  bool terminate;
  bool seekEnabled;
  bool seekDone;
  uint64_t duration = Gst::CLOCK_TIME_NONE;
};

static void handleMessage(CustomData *data, const Glib::RefPtr<Gst::Message> &msg);

TEST_CASE("tutorial_4", "[gst]") {
  CustomData data;
  Gst::init();

  data.playbin = Gst::PlayBin::create("playbin");
  data.playbin->set_property("uri",
                             Glib::ustring("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"));
  data.playbin->set_state(Gst::State::STATE_PLAYING);
  auto bus = data.playbin->get_bus();


}