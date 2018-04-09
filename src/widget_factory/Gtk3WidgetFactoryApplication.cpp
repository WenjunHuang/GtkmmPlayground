//
// Created by xxzyjy on 2018/1/27.
//
#include <iostream>
#include <boost/format.hpp>
#include "Gtk3WidgetFactoryApplication.h"

Gtk3WidgetFactoryApplication::Gtk3WidgetFactoryApplication() : Gtk::Application("org.gtk.WidgetFactory",
                                                                                Gio::APPLICATION_FLAGS_NONE) {
  addActionEntries();
  setupOptions();
}

void Gtk3WidgetFactoryApplication::setupOptions() {
  add_main_option_entry(OPTION_TYPE_BOOL, "version", '\0', "Show program version");
  signal_handle_local_options().connect(sigc::mem_fun(*this, &Gtk3WidgetFactoryApplication::onLocalOptions));
}

void Gtk3WidgetFactoryApplication::addActionEntries() {
  add_action("about", sigc::mem_fun(*this, &Gtk3WidgetFactoryApplication::onActionAbout));
  add_action("quit", sigc::mem_fun(*this, &Gtk3WidgetFactoryApplication::onActionQuit));
  add_action_radio_string("main", "'steak'");

  auto action = add_action_bool("wine", false);
  action->set_enabled(false);

  add_action_bool("beer", false);
  add_action_bool("water", true);
  add_action_radio_string("dessert", "'bars'");
  add_action_radio_string("pay", "");


}

int Gtk3WidgetFactoryApplication::onLocalOptions(const Glib::RefPtr<Glib::VariantDict> &variantDic) {
  bool version = false;
  variantDic->lookup_value("version", version);
  if (version) {
    printVersion();
    return 0;
  }
  return -1;
}

void Gtk3WidgetFactoryApplication::printVersion() {
  std::cout << boost::format("gtk3-widget-factory %d.%d.%d\n")
               % gtk_get_major_version()
               % gtk_get_minor_version()
               % gtk_get_micro_version() << std::endl;
}

void Gtk3WidgetFactoryApplication::on_activate() {
  // load css
  auto cssProvider = Gtk::CssProvider::create();
  cssProvider->load_from_path("/org/gtk/WidgetFactory/widget-factory.css");

  Gtk::StyleContext::add_provider_for_screen(
    Gdk::Screen::get_default(),
    cssProvider,
    GTK_STYLE_PROVIDER_PRIORITY_USER);

  auto builder = Gtk::Builder::create_from_resource("/org/gtkmm/WidgetFactory/widget-factory.ui");



}

void Gtk3WidgetFactoryApplication::onActionAbout() {

}

void Gtk3WidgetFactoryApplication::onActionQuit() {

}

Gtk3WidgetFactoryApplication::~Gtk3WidgetFactoryApplication() {

}
