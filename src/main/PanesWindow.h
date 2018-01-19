#pragma once


#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/paned.h>
#include <gtkmm/textview.h>

class MessagesList : public Gtk::ScrolledWindow {
public:
  MessagesList();

  virtual ~MessagesList();

  class ModelColumns : public Gtk::TreeModel::ColumnRecord {
  public:
    ModelColumns() {
      add(_colText);
    }

    Gtk::TreeModelColumn<Glib::ustring> _colText;
  };

  ModelColumns _columns;
protected:
  Glib::RefPtr<Gtk::ListStore> _refListStore;
  Gtk::TreeView _treeView;
};

class MessageText : public Gtk::ScrolledWindow {
public:
  MessageText();

  virtual ~MessageText();

  void insert_text();

protected:
  Gtk::TextView _textView;
};

class PanesWindow : public Gtk::Window {
public:
  PanesWindow();

  virtual ~PanesWindow();

protected:
  Gtk::Paned _vpaned;
  MessagesList _messagesList;
  MessageText _messageText;
};



