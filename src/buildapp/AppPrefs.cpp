//
// Created by xxzyjy on 2018/1/25.
//

#include <iostream>
#include "AppPrefs.h"

AppPrefs::AppPrefs(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder) :
  Gtk::Dialog(cobject),
  _refBuilder{refBuilder} {
  _refBuilder->get_widget("font",_font);
  _refBuilder->get_widget("transition",_transition);

  _settings = Gio::Settings::create("org.gtkmm.exampleapp");
  _settings->bind("font",_font->property_font_name());
  _settings->bind("transition",_transition->property_active_id());

}

AppPrefs *AppPrefs::create(Gtk::Window &parent) {
  auto refBuilder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/prefs.glade");
  AppPrefs *dialog = nullptr;
  refBuilder->get_widget_derived("prefs_dialog",dialog);
  std::cout << "Is Dialog Model?"<<dialog->get_modal() << std::endl;
  dialog->set_modal(true);
  dialog->set_transient_for(parent);
  return dialog;
}
