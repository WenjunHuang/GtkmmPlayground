//
// Created by rick on 2018/1/23.
//

#pragma once

#include <gtkmm.h>

class AllWidgets : public Gtk::Window {
public:
    AllWidgets();

    virtual ~AllWidgets();

    void createBasicWidgets();

private:
    Gtk::Button button;
    Gtk::Label label;

};



