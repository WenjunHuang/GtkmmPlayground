//
// Created by rick on 2018/1/22.
//

#pragma once

#include <gtkmm.h>
class EventBoxExample : public Gtk::Window{
public:
    EventBoxExample();
    virtual ~EventBoxExample();

protected:
    bool on_eventbox_button_press(GdkEventButton *buttonEvent);

    Gtk::EventBox eventBox;
    Gtk::Label label;

};



