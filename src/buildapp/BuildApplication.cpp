//
// Created by rick on 2018/1/24.
//

#include "BuildApplication.h"

BuildApplication::BuildApplication() :
        Gtk::Application("org.gtkmm.examples.application", Gio::APPLICATION_HANDLES_OPEN) {

}

Glib::RefPtr<BuildApplication> BuildApplication::create() {
    return Glib::RefPtr<BuildApplication>(new BuildApplication);
}

MainWindow *BuildApplication::create_appwindow() {
    auto appwindow = new MainWindow;
    add_window(*appwindow);
    appwindow->signal_hide().connect(sigc::bind<Gtk::Window *>(
            sigc::mem_fun(*this, &BuildApplication::on_hide_window), appwindow
    ));
    return appwindow;
}

void BuildApplication::on_activate() {
    auto appwindow = create_appwindow();
    appwindow->present();
}

void BuildApplication::on_open(const Gio::Application::type_vec_files &files, const Glib::ustring &hint) {
    MainWindow *appwindow = nullptr;
    auto windows = get_windows();
    if (windows.size() > 0)
        appwindow = dynamic_cast<MainWindow *>(windows[0]);

    if (!appwindow)
        appwindow = create_appwindow();

    for (const auto& file: files)
        appwindow->open_file_view(file);

    appwindow->present();
}

void BuildApplication::on_hide_window(Gtk::Window *window) {
    delete window;
}
