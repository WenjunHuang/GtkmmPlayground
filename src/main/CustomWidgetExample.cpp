//
// Created by xxzyjy on 2018/1/26.
//

#include <iostream>
#include "CustomWidgetExample.h"
#include "catch.hpp"

MyWidget::MyWidget() :
  Glib::ObjectBase("mywidget"),
  Gtk::Widget(),
  _scaleProp(*this, "example_scale", 500),
  _scale(1000) {
  set_has_window(true);
  std::cout << "GType name:" << G_OBJECT_TYPE_NAME(gobj()) << std::endl;
  std::cout << "GType is a GtkWidget?:" << GTK_IS_WIDGET(gobj()) << std::endl;

  // Set the widget name to use in the CSS file.
  set_name("my-widget");

  _refCssProvider = Gtk::CssProvider::create();
  auto refStyleContext = get_style_context();
  refStyleContext->add_provider(_refCssProvider,
                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  _refCssProvider->signal_parsing_error().connect(
    sigc::mem_fun(*this, &MyWidget::on_parsing_error)
  );

  _refCssProvider->load_from_path("../src/main/custom_gtk.css");

}

MyWidget::~MyWidget() {

}

Gtk::SizeRequestMode MyWidget::get_request_mode_vfunc() const {
  return Gtk::Widget::get_request_mode_vfunc();
}

void MyWidget::get_preferred_width_vfunc(int &minimum_width, int &natural_width) const {
  minimum_width = 60;
  natural_width = 100;
}

void MyWidget::get_preferred_height_for_width_vfunc(int width, int &minimum_height, int &natural_height) const {
  minimum_height = 50;
  natural_height = 70;
}

void MyWidget::get_preferred_height_vfunc(int &minimum_height, int &natural_height) const {
  minimum_height = 50;
  natural_height = 70;
}

void MyWidget::get_preferred_width_for_height_vfunc(int height, int &minimum_width, int &natural_width) const {
  minimum_width = 60;
  natural_width = 100;
}

void MyWidget::on_size_allocate(Gtk::Allocation &allocation) {
  set_allocation(allocation);

  if (_refGdkWindow) {
    _refGdkWindow->move_resize(allocation.get_x(),
                               allocation.get_y(),
                               allocation.get_width(),
                               allocation.get_height());
  }
}

void MyWidget::on_map() {
  Widget::on_map();
}

void MyWidget::on_unmap() {
  Widget::on_unmap();
}

void MyWidget::on_realize() {
  set_realized();

  // Get the themed style from the CSS file:
  _scale = _scaleProp.get_value();
  std::cout << "_scale (example_scale from the theme/css-file) is: " << _scale << std::endl;
  if (!_refGdkWindow) {
    GdkWindowAttr attributes;
    memset(&attributes, 0, sizeof(attributes));

    auto allocation = get_allocation();

    // Set initial position and size of the Gdk::Window:
    attributes.x = allocation.get_x();
    attributes.y = allocation.get_y();
    attributes.width = allocation.get_width();
    attributes.height = allocation.get_height();
    attributes.event_mask = get_events() | Gdk::EXPOSURE_MASK;
    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.wclass = GDK_INPUT_OUTPUT;

    _refGdkWindow = Gdk::Window::create(get_parent_window(),
                                        &attributes,
                                        GDK_WA_X | GDK_WA_Y);
    set_window(_refGdkWindow);
    _refGdkWindow->set_user_data(gobj());
  }
}

void MyWidget::on_unrealize() {
  _refGdkWindow.reset();
  Gtk::Widget::on_unrealize();
}

bool MyWidget::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
  const auto allocation = get_allocation();
  const auto scale_x = (double) allocation.get_width() / _scale;
  const auto scale_y = (double) allocation.get_height() / _scale;
  auto refStyleContext = get_style_context();

  // paint the background
  refStyleContext->render_background(cr,
                                     allocation.get_x(),
                                     allocation.get_y(),
                                     allocation.get_width(),
                                     allocation.get_height());

  // draw the foreground
  const auto state = refStyleContext->get_state();
  Gdk::Cairo::set_source_rgba(cr, refStyleContext->get_color(state));
  cr->move_to(155. * scale_x, 165. * scale_y);
  cr->line_to(155. * scale_x, 838. * scale_y);
  cr->line_to(265. * scale_x, 900. * scale_y);
  cr->line_to(849. * scale_x, 564. * scale_y);
  cr->line_to(849. * scale_x, 438. * scale_y);
  cr->line_to(265. * scale_x, 100. * scale_y);
  cr->line_to(155. * scale_x, 165. * scale_y);
  cr->move_to(265. * scale_x, 100. * scale_y);
  cr->line_to(265. * scale_x, 652. * scale_y);
  cr->line_to(526. * scale_x, 502. * scale_y);
  cr->move_to(369. * scale_x, 411. * scale_y);
  cr->line_to(633. * scale_x, 564. * scale_y);
  cr->move_to(369. * scale_x, 286. * scale_y);
  cr->line_to(369. * scale_x, 592. * scale_y);
  cr->move_to(369. * scale_x, 286. * scale_y);
  cr->line_to(849. * scale_x, 564. * scale_y);
  cr->move_to(633. * scale_x, 564. * scale_y);
  cr->line_to(155. * scale_x, 838. * scale_y);
  cr->stroke();

  return true;
}

void MyWidget::on_parsing_error(const Glib::RefPtr<const Gtk::CssSection> &section, const Glib::Error &error) {
  std::cerr << "on_parsing_error(): " << error.what() << std::endl;
  if (section) {
    const auto file = section->get_file();
    if (file) {
      std::cerr << "  URI = " << file->get_uri() << std::endl;
    }

    std::cerr << "  start_line = " << section->get_start_line() + 1
              << ", end_line = " << section->get_end_line() + 1 << std::endl;
    std::cerr << "  start_position = " << section->get_start_position()
              << ", end_position = " << section->get_end_position() << std::endl;
  }
}

CustomWidgetExample::CustomWidgetExample() :
  _vbox(Gtk::ORIENTATION_VERTICAL),
  _buttonQuit("Quit") {
  set_title("Custom Widget example");
  set_border_width(6);
  set_default_size(400, 200);

  add(_vbox);
  _vbox.pack_start(_myWidget, Gtk::PACK_EXPAND_WIDGET);
  _myWidget.show();

  _vbox.pack_start(_buttonBox, Gtk::PACK_SHRINK);

  _buttonBox.pack_start(_buttonQuit, Gtk::PACK_SHRINK);
  _buttonBox.set_border_width(6);
  _buttonBox.set_layout(Gtk::BUTTONBOX_END);
  _buttonQuit.signal_clicked().connect(sigc::mem_fun(*this, &CustomWidgetExample::on_button_quit));

  show_all_children();

}

CustomWidgetExample::~CustomWidgetExample() {

}

void CustomWidgetExample::on_button_quit() {
  hide();
}

TEST_CASE("custom_widget", "[gtkmm]") {
  auto app = Gtk::Application::create("org.gtkmm.example");
  CustomWidgetExample window;
  app->run(window);
}
