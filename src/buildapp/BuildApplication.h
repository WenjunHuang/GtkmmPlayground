//
// Created by rick on 2018/1/24.
//

#pragma once


#include "MainWindow.h"

class BuildApplication : public Gtk::Application {
protected:
    BuildApplication();

public:
    static Glib::RefPtr<BuildApplication> create();

protected:
    void on_activate() override;

    void on_open(const Gio::Application::type_vec_files &files,
                 const Glib::ustring &hint) override;

private:
    MainWindow *create_appwindow();

    void on_hide_window(Gtk::Window *window);

};



