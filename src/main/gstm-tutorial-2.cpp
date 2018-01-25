//
// Created by xxzyjy on 2018/1/19.
//

#include "catch.hpp"
#include "TestFixture.h"
#include <gstreamermm.h>
#include <iostream>

TEST_CASE("tutorial_2", "[gstmm]") {
  Gst::init();
  auto source = Gst::VideoTestSrc::create("source");
  auto sink = Gst::ElementFactory::create_element("autovideosink", "sink");
  auto filter = Gst::ElementFactory::create_element("vertigotv");
  auto pipeline = Gst::Pipeline::create("test-pipeline");

  if (!pipeline || !source || !sink) {
    std::cerr << "Not all elements could be created" << std::endl;
    FAIL();
  }

  try {
    pipeline->add(source)
            ->add(filter)
            ->add(sink);
    source->link(filter);
    filter->link(sink);
  } catch (std::runtime_error &error) {
    FAIL(error.what());
  }

  source->set_property("pattern", Gst::VideoTestSrcPattern::VIDEO_TEST_SRC_SMPTE);
  auto ret = pipeline->set_state(Gst::State::STATE_PLAYING);
  if (ret == Gst::STATE_CHANGE_FAILURE) {
    std::cerr << "Unable to set the pipeline to the playing state" << std::endl;
    FAIL();
  }

  auto bus = pipeline->get_bus();

  while(true) {
    auto msg = bus->pop(Gst::CLOCK_TIME_NONE, Gst::MESSAGE_ERROR | Gst::MESSAGE_EOS);
    if (msg) {
      switch (msg->get_message_type()) {
        case Gst::MESSAGE_ERROR: {
          auto errorMsg = Glib::RefPtr<Gst::MessageError>::cast_static(msg);
          std::cerr << msg->get_source()->get_name()
                    << errorMsg->parse_error().what()
                    << std::endl;
          FAIL();
          break;
        }
        case Gst::MESSAGE_EOS:
          std::cout << "End-Of-Stream reached" << std::endl;
              break;
        default:
          std::cerr << "Unexpected message received" << std::endl;
              break;
      }
    }
  }

  pipeline->set_state(Gst::STATE_NULL);
}