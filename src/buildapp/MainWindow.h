//
// Created by rick on 2018/1/24.
//

#pragma once

#include <gtkmm.h>


class MainWindow : public Gtk::ApplicationWindow {
public:
  MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder);

  static MainWindow *create();

  void open_file_view(const Glib::RefPtr<Gio::File> &file);

protected:
  void update_words();
  void update_lines();
  void on_search_text_changed();
  void on_visible_child_changed();
  void on_reveal_child_changed();
  void on_find_word(const Gtk::Button* button);

  Glib::RefPtr<Gtk::Builder> _refBuilder;
  Gtk::Stack *_stack;
  Glib::RefPtr<Gio::Settings> _settings;
  Gtk::ToggleButton *_search;
  Gtk::SearchBar *_searchbar;
  Gtk::SearchEntry *_searchentry;
  Gtk::MenuButton *_gears;
  Gtk::Revealer *_sidebar;
  Gtk::ListBox *_words;
  Gtk::Label * _lines;
  Gtk::Label *_lines_label;

  Glib::RefPtr<Glib::Binding> _binding_search_enabled;
  Glib::RefPtr<Glib::Binding> _binding_lines_visible;

};



