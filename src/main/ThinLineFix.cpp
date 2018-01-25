//
// Created by rick on 2018/1/23.
//

#include "catch.hpp"
#include "TestFixture.h"
#include "ThinLineFix.h"

ThinLineFix::ThinLineFix() : buttonFixLines("Fix lines") {
    set_title("Thin lines example");
    container.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    container.attach(areaLines,0,0,2,2);
    container.attach(buttonFixLines,2,0,1,1);

    add(container);

    buttonFixLines.signal_toggled().connect(
            sigc::mem_fun(*this, &ThinLineFix::on_button_toggled)
    );

    on_button_toggled();

    show_all_children();


}

ThinLineFix::~ThinLineFix() {

}

void ThinLineFix::on_button_toggled() {
    areaLines.fixLines(buttonFixLines.get_active());
}

MyArea::MyArea() : fixValue(0) {
    set_size_request(200, 100);
}

MyArea::~MyArea() {

}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    auto allocation = get_allocation();
    auto width = allocation.get_width();
    auto height = allocation.get_height();

//    cr->set_source_rgb(0.8,0.0,0.0);
    cr->set_line_width(1.0);
    for (int i = 0; i < width; i += 2) {
        cr->move_to(i + fixValue, 0);
        cr->line_to(i + fixValue, height);
    }
    cr->stroke();

    return true;
}

void MyArea::fixLines(bool fix) {
    fixValue = fix ? 0.5 : 0.0;
    forceRedraw();

}

void MyArea::forceRedraw() {
    auto win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }

}

TEST_CASE("fix_line", "[gtkmm]") {
    ThinLineFix window;
    app->run(window);
}
