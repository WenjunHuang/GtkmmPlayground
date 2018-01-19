//
// Created by xxzyjy on 2018/1/19.
//

#include <gstreamermm.h>
#include <iostream>
#include "catch.hpp"

using namespace Gst;

struct CustomData {
  Glib::RefPtr<Pipeline> pipeline;
  Glib::RefPtr<UriDecodeBin> source;
  Glib::RefPtr<AudioConvert> convert;
  Glib::RefPtr<VideoConvert> videoConvert;
  Glib::RefPtr<Element> sink;
  Glib::RefPtr<Element> videoSink;

  void addToPipeline() {
    pipeline->add(source)
            ->add(convert)
            ->add(videoConvert)
            ->add(sink)
            ->add(videoSink);
  }
};

void pad_added_handler(const Glib::RefPtr<Gst::Pad> &newPad, CustomData *data) {
  std::cout << "Received new pad " << newPad->get_name() << " from " << data->source->get_name() << std::endl;

  Glib::RefPtr<Gst::Caps> newPadCaps = newPad->query_caps(Glib::RefPtr<Gst::Caps>());
  auto newPadStruct = newPadCaps->get_structure(0);
  auto newPadName = newPadStruct.get_name();
  if (newPadName.find("audio/x-raw") != std::string::npos) {
    // 连接音频pad
    auto sinkPad = data->convert->get_static_pad("sink");
    if (sinkPad->is_linked()) {
      std::cout << "We are already linked. Ignoring\n";
      return;
    }

    if (newPad->link(sinkPad) != PadLinkReturn::PAD_LINK_OK) {
      std::cerr << "Link error" << std::endl;
    } else {
      std::cout << "link succedeed" << std::endl;
    }
  } else if (newPadName.find("video") != std::string::npos) {
    //连接视频pad
//    auto sinkPad = data->videoConvert->get_static_pad("video_sink");
//    if (data->videoSink->))) {
//      std::cout << "Video sink has been linked";
//      return;
//    }

    newPad->link(data->videoConvert->get_static_pad("sink"));
  }

}

TEST_CASE("dynamic_helloworld", "[gst]") {
  Gst::init();

  CustomData data;
  data.source = UriDecodeBin::create("source");
  data.convert = AudioConvert::create("convert");
  data.videoConvert = VideoConvert::create("video_convert");
  data.sink = ElementFactory::create_element("autoaudiosink", "sink");
  data.videoSink = ElementFactory::create_element("autovideosink", "video_sink");
  data.pipeline = Pipeline::create("test-pipeline");
  data.addToPipeline();

  data.convert->link(data.sink);
  data.videoConvert->link(data.videoSink);

  data.source->set_property("uri",
                            Glib::ustring(
                              "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"));

  data.source->signal_pad_added().connect(sigc::bind(
    sigc::ptr_fun(pad_added_handler),
    &data));

  data.pipeline->set_state(State::STATE_PLAYING);

  GMainLoop *main_loop = g_main_loop_new(nullptr, false);
  g_main_loop_run(main_loop);

  data.pipeline->set_state(State::STATE_NULL);
}
