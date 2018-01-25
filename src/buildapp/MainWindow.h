//
// Created by rick on 2018/1/24.
//

#pragma once
#include <gtkmm.h>


class MainWindow :public Gtk::ApplicationWindow {
public:
    MainWindow();

    void open_file_view(const Glib::RefPtr<Gio::File> &file);

};



