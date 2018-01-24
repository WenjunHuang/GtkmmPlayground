//
// Created by rick on 2018/1/22.
//

#include <TestFixture.h>
#include "catch.hpp"
#include "EventBoxExample.h"

EventBoxExample::EventBoxExample() {
    label.set_label("Click here to quit,quit,quit,quit,quit");
    set_title("EventBox");
    set_border_width(10);

    add(eventBox);

    eventBox.add(label);

    set_default_size(110,20);
    label.set_size_request(110,20);
    label.set_ellipsize(Pango::ELLIPSIZE_END);

    eventBox.set_events(Gdk::BUTTON_PRESS_MASK);
    eventBox.signal_button_press_event().connect(
            sigc::mem_fun(*this,&EventBoxExample::on_eventbox_button_press));
    eventBox.set_tooltip_text("Click me!");

    show_all_children();

}

bool EventBoxExample::on_eventbox_button_press(GdkEventButton *buttonEvent) {
    hide();
    return true;
}

EventBoxExample::~EventBoxExample() {

}

TEST_CASE("event_box","[gtkmm]"){
    EventBoxExample window;
    app->run(window);
}
