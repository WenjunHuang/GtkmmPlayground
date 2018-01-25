//
// Created by xxzyjy on 2018/1/19.
//

#include <boost/format.hpp>
#include <gtkmm.h>
#include <gstreamermm.h>
#include <iostream>
#include <cstdlib>
#include "TestFixture.h"
#include "catch.hpp"

auto format_ns(uint64_t ns) {
    auto s = std::lldiv(ns, 1000000000);
    auto m = std::lldiv(s.quot, 60);
    auto h = std::lldiv(m.quot, 60);


    auto f =  boost::format("%1%:%2%:%3%.%4%") % h.quot % h.rem % m.rem % s.rem;
    return f;
}

class GstBasicTutorial4 {
public:
    GstBasicTutorial4();

    ~GstBasicTutorial4();

    void play();

private:
    void handleMessage(const Glib::RefPtr<Gst::Message> &msg);

public:
    Glib::RefPtr<Gst::PlayBin> playbin;
    bool playing = false;
    bool terminate = false;
    bool seekEnabled = false;
    bool seekDone = false;
    gint64 duration = Gst::CLOCK_TIME_NONE;

    Gtk::Window window;
    Gtk::Widget *drawingArea;
};

GstBasicTutorial4::GstBasicTutorial4() {
    Gst::init();
    window.set_size_request(640,480);
//    window.add(drawingArea);
//
//    drawingArea.signal_realize().connect([=](){
//        guintptr hwnd = (guintptr)gdk_win32_window_get_impl_hwnd(drawingArea.get_window()->gobj());
//        playbin->set_window_handle(hwnd);
//    });

    playbin = Gst::PlayBin::create("playbin");
    auto videoSink = Gst::ElementFactory::create_element("gtksink","videosink");
    playbin->set_property("video_sink",videoSink);
    videoSink->get_property("widget",drawingArea);
    window.add(*drawingArea);

    if (!playbin)
        throw std::runtime_error("Error: Can not initialize playbin");

    playbin->set_property("uri",
                          Glib::ustring(
                                  "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"));
    window.show_all();
}

GstBasicTutorial4::~GstBasicTutorial4() {
    playbin->set_state(Gst::State::STATE_NULL);
}

void GstBasicTutorial4::play() {
    if (playing)
        return;

    auto ret = playbin->set_state(Gst::State::STATE_PLAYING);
    if (ret == Gst::StateChangeReturn::STATE_CHANGE_FAILURE) {
        throw std::runtime_error("Error: Unable to set the pipeline to the playing state");
    }

    /*
    try {
        auto bus = playbin->get_bus();
        while (true) {
            auto msg = bus->pop(100 * Gst::MILLI_SECOND,
                                Gst::MessageType::MESSAGE_STATE_CHANGED | Gst::MessageType::MESSAGE_ERROR |
                                Gst::MessageType::MESSAGE_EOS | Gst::MessageType::MESSAGE_DURATION_CHANGED);

            if (msg) {
                handleMessage(msg);
            } else {
                if (playing) {
                    gint64 current = -1;
                    if (!playbin->query_position(Gst::Format::FORMAT_TIME, current)) {
                        std::cerr << "Error: Could not query current position" << std::endl;
                    }

                    // if we don't know it yet, query the duration
                    if (duration == Gst::CLOCK_TIME_NONE) {
                        if (!playbin->query_duration(Gst::Format::FORMAT_TIME, duration))
                            std::cerr << "Error: Could not query duration " << std::endl;
                    }

                    std::cout << boost::format("Position %1% / %2%") % format_ns(current) % format_ns(duration) << std::endl;

                    if (seekEnabled && !seekDone && current > 10 * Gst::SECOND) {
                        std::cout << "Reached 10s, performing seek..." << std::endl;
                        playbin->seek(Gst::Format::FORMAT_TIME,
                                      Gst::SeekFlags::SEEK_FLAG_FLUSH | Gst::SeekFlags::SEEK_FLAG_KEY_UNIT,
                                      30 * Gst::SECOND);
                        seekDone = true;
                    }
                }
            }
            if (terminate)
                break;

        }
    } catch (const std::exception &e) {
        std::cerr << boost::format("Error in loop %1") % e.what() << std::endl;
    }
*/
}

void GstBasicTutorial4::handleMessage(const Glib::RefPtr<Gst::Message> &msg) {
    auto t = msg->get_message_type();
    if (t == Gst::MessageType::MESSAGE_ERROR) {
        auto errorMsg = Glib::RefPtr<Gst::MessageError>::cast_static(msg);
        auto err = errorMsg->parse_error();
        std::cerr << boost::format("Error: %1:%2") % errorMsg->get_source()->get_name() % err.what() << std::endl;
    } else if (t == Gst::MessageType::MESSAGE_EOS) {
        std::cout << "End-Of-Stream reached" << std::endl;
        terminate = true;
    } else if (t == Gst::MessageType::MESSAGE_DURATION_CHANGED) {
        duration = Gst::CLOCK_TIME_NONE;
    } else if (t == Gst::MessageType::MESSAGE_STATE_CHANGED) {
        auto msgStateChanged = Glib::RefPtr<Gst::MessageStateChanged>::cast_static(msg);
        Gst::State oldState, newState, pendingState;
        msgStateChanged->parse(oldState, newState, pendingState);

        if (msgStateChanged->get_source() == playbin) {
            std::cout << boost::format("Pipeline state changed from '%s' to '%s'")
                         % Gst::Enums::get_name(oldState)
                         % Gst::Enums::get_name(newState) << std::endl;
            playing = newState == Gst::State::STATE_PLAYING;

            if (playing) {
                auto query = Gst::Query::create_seeking(Gst::Format::FORMAT_TIME);
                if (playbin->query(query)) {
                    auto querySeeking = Glib::RefPtr<Gst::QuerySeeking>::cast_static(query);
                    Gst::Format format;
                    gint64 segment_start;
                    gint64 segment_end;
                    querySeeking->parse(format,seekEnabled,segment_start,segment_end);
                    if (seekEnabled){
                        std::cout << boost::format("Seeking is ENABLED (from %1% to %2%") % format_ns(segment_start) % format_ns(segment_end) << std::endl;
                    } else {
                        std::cout << "Seeking is DISALED for this stream" << std::endl;
                    }
                } else {
                    std::cerr << "Error: Seeking query failed" << std::endl;
                }
            }
        }
    } else {
        std::cerr << "Error: Unexpected message received" << std::endl;
    }
}


TEST_CASE("tutorial_4", "[gst]") {
    GstBasicTutorial4 player;
    player.play();
    app->run(player.window);

}