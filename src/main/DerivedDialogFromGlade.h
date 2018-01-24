//
// Created by rick on 2018/1/24.
//

#pragma once
#include <gtkmm.h>

class DerivedDialog : public Gtk::Dialog {
public:
    DerivedDialog(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& builder);
    DerivedDialog(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& builder,bool isGlad);
    virtual ~DerivedDialog();
protected:
    void on_button_quit();

    Glib::RefPtr<Gtk::Builder> refGlade;
    Gtk::Button *button;

};




