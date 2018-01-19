#pragma once


#include <gtkmm/window.h>
#include <gtkmm/frame.h>

class FrameWindow : public Gtk::Window{
public:
  FrameWindow();
  virtual ~FrameWindow();
protected:
  Gtk::Frame _frame;

};



