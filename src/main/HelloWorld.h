#pragma once


#include <gtkmm/window.h>
#include <gtkmm/button.h>

class HelloWorld : public Gtk::Window {
public:
  HelloWorld();

protected:
  Gtk::Button _button;

};



