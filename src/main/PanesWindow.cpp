//
// Created by xxzyjy on 2018/1/14.
//

#include <catch.hpp>
#include <iostream>
#include "TestFixture.h"
#include "PanesWindow.h"
MessagesList::MessagesList() {
  set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  add(_treeView);
  _refListStore = Gtk::ListStore::create(_columns);
  _treeView.set_model(_refListStore);

  for (int i = 0; i < 10; ++i) {
    std::ostringstream text;
    text << "message #" << i;
    Gtk::TreeModel::Row row = *(_refListStore->append());
    row[_columns._colText] = text.str();
  }

  _treeView.append_column("Messages", _columns._colText);
  signal_show().connect([=](){
//   auto win = get_window()->gobj();
    std::cout << "show" << std::endl;
  });
  show_all_children();
}

MessagesList::~MessagesList() {

}

MessageText::MessageText() {
  set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  add(_textView);
  insert_text();
  show_all_children();
}

MessageText::~MessageText() {

}

void MessageText::insert_text() {
  auto refTextBuffer = _textView.get_buffer();
  auto iter = refTextBuffer->get_iter_at_offset(0);
  refTextBuffer->insert(iter,
                        "From: pathfinder@nasa.gov\n"
                          "To: mom@nasa.gov\n"
                          "Subject: Made it!\n"
                          "\n"
                          "We just got in this morning. The weather has been\n"
                          "great - clear but cold, and there are lots of fun sights.\n"
                          "Sojourner says hi. See you soon.\n"
                          " -Path\n");

}

PanesWindow::PanesWindow():_vpaned(Gtk::ORIENTATION_VERTICAL) {
  set_title("Paned Windows");
  set_border_width(10);
  set_default_size(450, 400);

  add(_vpaned);
  _vpaned.add1(_messagesList);
  _vpaned.add2(_messageText);
}

PanesWindow::~PanesWindow() {

}

TEST_CASE("panes_window","[gtkmm]"){
  PanesWindow window;
  window.show_all();
  auto w =window.get_window()->get_toplevel()->gobj();
  app->run(window);
}
