//
// Created by rick on 2018/1/23.
//

#pragma once

#include <gtkmm.h>

class CustomContainer : public Gtk::Container {
public:
    CustomContainer();
    virtual ~CustomContainer();

    void setChildWidgets(Gtk::Widget &childOne,Gtk::Widget &childTwo);

protected:
    Gtk::SizeRequestMode get_request_mode_vfunc() const override;

    void on_add(Widget *widget) override;

    void on_remove(Widget *widget) override;

    GType child_type_vfunc() const override;

    void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data) override;

    void on_size_allocate(Gtk::Allocation &allocation) override;

    void get_preferred_width_vfunc(int &minimum_width, int &natural_width) const override;

    void get_preferred_height_for_width_vfunc(int width, int &minimum_height, int &natural_height) const override;

    void get_preferred_height_vfunc(int &minimum_height, int &natural_height) const override;

    void get_preferred_width_for_height_vfunc(int height, int &minimum_width, int &natural_width) const override;

private:
    Gtk::Widget *childOne;
    Gtk::Widget *childTwo;
};


class CustomContainerExample {

};



