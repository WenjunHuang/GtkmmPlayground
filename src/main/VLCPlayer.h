#pragma once
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/drawingarea.h>
#include <vlc/libvlc.h>
#include <vlc/libvlc_media_list_player.h>

class VLCPlayerExample : public Gtk::Window {
public:
  VLCPlayerExample();
  virtual ~VLCPlayerExample();
private:
  bool playerPaused;
  bool isPlayerActive;
  Gtk::DrawingArea drawingArea;

  void togglePlayerPlayback();
  void stopPlayer();
  void realized();

  libvlc_instance_t* instance;
  libvlc_media_player_t* player;

};



