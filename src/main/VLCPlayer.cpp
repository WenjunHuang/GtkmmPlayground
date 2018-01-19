//
// Created by xxzyjy on 2018/1/19.
//

#include <gtkmm/stock.h>
#include <gtkmm/hvbox.h>
#include <catch.hpp>
#include <vlc/vlc.h>
#include "TestFixture.h"
#include "VLCPlayer.h"
#include "mac_utils.h"

VLCPlayerExample::VLCPlayerExample() {
  set_title("VLCPlayer Example");

  auto playbackButton = Gtk::manage(new Gtk::Button);
  auto playbackImage = Gtk::manage(new Gtk::Image(Gtk::Stock::MEDIA_PLAY,
                                                  Gtk::BuiltinIconSize::ICON_SIZE_MENU));
  playbackButton->set_image(*playbackImage);
  playbackButton->signal_clicked().connect(sigc::mem_fun(this, &VLCPlayerExample::togglePlayerPlayback));

  auto stopButton = Gtk::manage(new Gtk::Button);
  auto stopImage = Gtk::manage(new Gtk::Image(Gtk::Stock::MEDIA_STOP,
                                              Gtk::BuiltinIconSize::ICON_SIZE_MENU));
  stopButton->set_image(*stopImage);
  stopButton->signal_clicked().connect(sigc::mem_fun(this, &VLCPlayerExample::stopPlayer));

  auto pauseButton = Gtk::manage(new Gtk::Button);
  auto pauseImage = Gtk::manage(new Gtk::Image(Gtk::Stock::MEDIA_PAUSE,
                                               Gtk::BuiltinIconSize::ICON_SIZE_MENU));
  pauseButton->set_image(*pauseImage);


  drawingArea.set_size_request(300, 300);
  drawingArea.signal_realize().connect(sigc::mem_fun(this, &VLCPlayerExample::realized));

  auto hbox = Gtk::manage(new Gtk::HBox);
  hbox->pack_start(*playbackButton);
  hbox->pack_start(*stopButton);

  auto vbox = Gtk::manage(new Gtk::VBox);
  vbox->pack_start(drawingArea);
  vbox->pack_start(*hbox);

  add(*vbox);
}

void VLCPlayerExample::togglePlayerPlayback() {

}

void VLCPlayerExample::stopPlayer() {

}

void VLCPlayerExample::realized() {
//  const char *argv[] = {"--no-xlib",
//                        "--plugin-path=/Applications/VLC.app/Contents/MacOS/plugins"};
  instance = libvlc_new(0, nullptr);
  player = libvlc_media_player_new(instance);
  // for mac
  auto win = drawingArea.get_window()->gobj();
  auto nswin = get_nswindow(win);
  libvlc_media_player_set_nsobject(player, nswin);
  auto m = libvlc_media_new_path(instance, "/Users/xxzyjy/Desktop/gravity.mpg");
  libvlc_media_player_set_media(player, m);
//  libvlc_media_release(m);
  libvlc_media_player_play(player);

}

VLCPlayerExample::~VLCPlayerExample() {

}

TEST_CASE("vlc_player", "[gtkmm]") {
  VLCPlayerExample window;
  window.show_all();
  app->run(window);
}
