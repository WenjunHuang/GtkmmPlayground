//
// Created by rick on 2018/1/24.
//

#include "catch.hpp"
#include "TestFixture.h"
#include <glibmm.h>
#include <gtkmm.h>
#include <iostream>
#include <memory>

std::unique_ptr<Gtk::Dialog> dialog;

static void on_button_clicked() {
    if (dialog)
        dialog->hide();
}

TEST_CASE("simple_glade", "[gtkmm]") {
    auto refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file("./src/glade/basic.glade");
    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError:" << ex.what() << std::endl;
    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError:" << ex.what() << std::endl;
    }
    Gtk::Dialog *pDialog = nullptr;
    refBuilder->get_widget("DialogBasic", pDialog);
    if (pDialog) {
        dialog.reset(pDialog);
        Gtk::Button *pButton = nullptr;
        refBuilder->get_widget("quit_button",pButton);
        if (pButton){
            pButton->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
        }
        app->run(*pDialog);
    }

}