//
// Created by rick on 2018/1/24.
//

#include "DerivedDialogFromGlade.h"
#include "catch.hpp"
#include "TestFixture.h"

TEST_CASE("derived", "[gtkmm]") {
    auto refBuilder = Gtk::Builder::create();
    refBuilder->add_from_file("src/glade/derived.glade");

    DerivedDialog *pDialog = nullptr;
    refBuilder->get_widget_derived("DialogDerived", pDialog,true);
    app->run(*pDialog);

    delete pDialog;

}

DerivedDialog::DerivedDialog(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) : Gtk::Dialog(cobject),
                                                                                                   refGlade(builder),
                                                                                                   button(nullptr) {
    refGlade->get_widget("quit_button",button);
    button->signal_clicked().connect(sigc::mem_fun(*this,&DerivedDialog::on_button_quit));
}

DerivedDialog::DerivedDialog(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder, bool isGlad):DerivedDialog(cobject,builder) {
    auto image = Gtk::manage(new Gtk::Image());
    image->set_from_icon_name(isGlad?"face-smile":"face-sad",Gtk::ICON_SIZE_DIALOG);
    image->show_all();
    get_content_area()->pack_start(*image);
}

DerivedDialog::~DerivedDialog() {

}

void DerivedDialog::on_button_quit() {
    hide();

}
