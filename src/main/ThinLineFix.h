//
// Created by rick on 2018/1/23.
//

#pragma once

#include <gtkmm.h>
class MyArea : public Gtk::DrawingArea {
public:
    MyArea();
    virtual ~MyArea();

    void fixLines(bool fix = true);
    void forceRedraw();
private:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
private:
    double fixValue;
};

class ThinLineFix : public Gtk::Window{
public:
    ThinLineFix();
    virtual ~ThinLineFix();
protected:
    void on_button_toggled();
private:
    Gtk::Grid container;
    MyArea areaLines;
    Gtk::CheckButton buttonFixLines;


};



