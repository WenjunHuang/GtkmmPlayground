#pragma once

#include <gtkmm.h>
class Gtk3WidgetFactoryApplication:public Gtk::Application {
public:
  Gtk3WidgetFactoryApplication();
  virtual ~Gtk3WidgetFactoryApplication();

protected:
  void on_activate() override ;
private:
  void onActionAbout();
  void onActionQuit();
  int onLocalOptions(const Glib::RefPtr<Glib::VariantDict> &variantDic);

  void addActionEntries();

  void printVersion();

  void setupOptions();
};



