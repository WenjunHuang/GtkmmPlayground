#pragma once

#include <gtkmm.h>

class AppPrefs : public Gtk::Dialog {
public:
  AppPrefs(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder);

  static AppPrefs *create(Gtk::Window &parent);

private:
  Glib::RefPtr<Gtk::Builder> _refBuilder;
  Glib::RefPtr<Gio::Settings> _settings;
  Gtk::FontButton *_font;
  Gtk::ComboBoxText *_transition;

};



