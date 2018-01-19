//
// Created by xxzyjy on 2018/1/14.
//

#include <catch.hpp>
#include "TestFixture.h"
#include "FrameWindow.h"

FrameWindow::FrameWindow() {
  set_title("Frame Example");
  set_size_request(300,300);

  set_border_width(10);

  add(_frame);

  _frame.set_label("Gtk::Frame Widget");
  _frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
  _frame.set_label_align(Gtk::ALIGN_END,Gtk::ALIGN_START);
  show_all_children();

}

FrameWindow::~FrameWindow() {

}

TEST_CASE("frame_window","[gtkmm]"){
  FrameWindow window;
  app->run(window);
}
