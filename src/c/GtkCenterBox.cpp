//
// Created by xxzyjy on 2018/1/27.
//
#include <gtkmm.h>

class CenterBox: public Gtk::Widget{
public:
  CenterBox();
  virtual ~CenterBox();

  void setStartWidget(const Glib::RefPtr<Gtk::Widget>& child);
  void setCenterWidget(const Glib::RefPtr<Gtk::Widget>& child);
  void setEndWidget(const Glib::RefPtr<Gtk::Widget>& child);

protected:
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;

  void get_preferred_width_vfunc(int &minimum_width, int &natural_width) const override;

  void get_preferred_height_for_width_vfunc(int width, int &minimum_height, int &natural_height) const override;

  void get_preferred_height_vfunc(int &minimum_height, int &natural_height) const override;

  void get_preferred_width_for_height_vfunc(int height, int &minimum_width, int &natural_width) const override;

private:
  Glib::RefPtr<Gtk::Widget> _startWidget;
  Glib::RefPtr<Gtk::Widget> _centerWidget;
  Glib::RefPtr<Gtk::Widget> _endWidget;
};

CenterBox::CenterBox() {

}

Gtk::SizeRequestMode CenterBox::get_request_mode_vfunc() const {
  return Gtk::SIZE_REQUEST_HEIGHT_FOR_WIDTH;
}

void CenterBox::get_preferred_width_vfunc(int &minimum_width, int &natural_width) const {
  Widget::get_preferred_width_vfunc(minimum_width, natural_width);
}

void CenterBox::get_preferred_height_for_width_vfunc(int width, int &minimum_height, int &natural_height) const {
  Widget::get_preferred_height_for_width_vfunc(width, minimum_height, natural_height);
}

void CenterBox::get_preferred_height_vfunc(int &minimum_height, int &natural_height) const {
  Widget::get_preferred_height_vfunc(minimum_height, natural_height);
}

void CenterBox::get_preferred_width_for_height_vfunc(int height, int &minimum_width, int &natural_width) const {
  Widget::get_preferred_width_for_height_vfunc(height, minimum_width, natural_width);
}

void CenterBox::setStartWidget(const Glib::RefPtr<Gtk::Widget> &child) {
  if (_startWidget)
    _startWidget->unparent();

  _startWidget = child;
  if (_startWidget)
    _startWidget->set_parent(*this);
}

void CenterBox::setCenterWidget(const Glib::RefPtr<Gtk::Widget> &child) {
  if (_centerWidget)
    _centerWidget->unparent();

  _centerWidget = child;
  if (_centerWidget)
    _centerWidget->set_parent(*this);

}

void CenterBox::setEndWidget(const Glib::RefPtr<Gtk::Widget> &child) {
  if(_endWidget)
    _endWidget->unparent();

  _endWidget = child;
  if (_endWidget)
    _endWidget->set_parent(*this);

}

CenterBox::~CenterBox() {

}
