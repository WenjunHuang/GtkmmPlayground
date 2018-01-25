#pragma once


#include <gtkmm.h>
#include <glibmm.h>

class ModelColumns: public Gtk::TreeModel::ColumnRecord {
public:
  ModelColumns() {
    add(colId);
    add(colName);
    add(colNumber);
    add(colPercentage);
  }

  Gtk::TreeModelColumn<uint32_t> colId;
  Gtk::TreeModelColumn<Glib::ustring> colName;
  Gtk::TreeModelColumn<uint16_t> colNumber;
  Gtk::TreeModelColumn<uint32_t> colPercentage;
};

class TreeViewExample: public Gtk::Window {
public:
  TreeViewExample();
  virtual ~TreeViewExample();
private:
  void on_button_quit();

  ModelColumns columns;

  Gtk::Button buttonQuit;
  Gtk::Box vbox;
  Gtk::ScrolledWindow scrolledWindow;
  Gtk::TreeView treeView;
  Glib::RefPtr<Gtk::ListStore> treeModel;

  Gtk::ButtonBox buttonBox;
};


