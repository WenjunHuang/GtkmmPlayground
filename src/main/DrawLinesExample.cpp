//
// Created by rick on 2018/1/23.
//

#include "catch.hpp"
#include "TestFixture.h"
#include "DrawLinesExample.h"

DrawLinesExample::DrawLinesExample() {

}

DrawLinesExample::~DrawLinesExample() {

}

bool DrawLinesExample::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    auto allocation = get_allocation();
    auto width = allocation.get_width();
    auto height = allocation.get_height();

    int xc = width / 2;
    int yc = height / 2;

    cr->set_line_width(10.0);
    cr->set_line_join(Cairo::LINE_JOIN_ROUND);

    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->move_to(0, 0);
    cr->line_to(xc, yc);
    cr->line_to(0, height);
    cr->stroke();

    return true;
}

TEST_CASE("draw_lines", "[gtkmm]") {
    Gtk::Window window;
    window.set_title("DrawingLines");

    DrawLinesExample area;
    window.add(area);
    area.show();

    app->run(window);
}