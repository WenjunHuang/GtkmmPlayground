//
// Created by rick on 2018/1/23.
//

#include "CustomContainerExample.h"

void CustomContainer::on_add(Gtk::Widget *widget) {
    Container::on_add(widget);
}

void CustomContainer::on_remove(Gtk::Widget *widget) {
    Container::on_remove(widget);
}

GType CustomContainer::child_type_vfunc() const {
    return Container::child_type_vfunc();
}

void CustomContainer::forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data) {
    Container::forall_vfunc(include_internals, callback, callback_data);
}

void CustomContainer::on_size_allocate(Gtk::Allocation &allocation) {
    Widget::on_size_allocate(allocation);
}

void CustomContainer::get_preferred_width_vfunc(int &minimum_width, int &natural_width) const {
    int childMinimumWidth[] = {0,0};
    int childNaturalWidth[] = {0,0};

    if (childOne && childOne->get_visible())
        childOne->get_preferred_width(childMinimumWidth[0],childNaturalWidth[0]);

    if (childTwo && childTwo->get_visible())
        childTwo->get_preferred_width(childMinimumWidth[1],childNaturalWidth[1]);

    minimum_width = std::max(childMinimumWidth[0],childMinimumWidth[1]);
    natural_width = std::max(childNaturalWidth[0],childNaturalWidth[1]);
}

void CustomContainer::get_preferred_height_for_width_vfunc(int width, int &minimum_height, int &natural_height) const {
    Widget::get_preferred_height_for_width_vfunc(width, minimum_height, natural_height);
}

void CustomContainer::get_preferred_height_vfunc(int &minimum_height, int &natural_height) const {
    Widget::get_preferred_height_vfunc(minimum_height, natural_height);
}

void CustomContainer::get_preferred_width_for_height_vfunc(int height, int &minimum_width, int &natural_width) const {
    Widget::get_preferred_width_for_height_vfunc(height, minimum_width, natural_width);
}

CustomContainer::CustomContainer() {
    set_has_window(false);
    set_redraw_on_allocate(false);

}

CustomContainer::~CustomContainer() {
    if (childOne)
        childOne->unparent();
    if (childTwo)
        childTwo->unparent();

}

void CustomContainer::setChildWidgets(Gtk::Widget &childOne, Gtk::Widget &childTwo) {
    this->childOne = &childOne;
    this->childTwo =  &childTwo;

    this->childOne->set_parent(*this);
    this->childTwo->set_parent(*this);

}

Gtk::SizeRequestMode CustomContainer::get_request_mode_vfunc() const {
    return Gtk::SIZE_REQUEST_HEIGHT_FOR_WIDTH;
}
