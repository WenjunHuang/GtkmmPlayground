//
// Created by rick on 2018/1/23.
//

#pragma once
#include <gtkmm.h>

class DrawLinesExample : public Gtk::DrawingArea {
public:
    DrawLinesExample();
    virtual ~DrawLinesExample();
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

};



