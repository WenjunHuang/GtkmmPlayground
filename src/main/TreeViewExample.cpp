//
// Created by xxzyjy on 2018/1/23.
//

#include "TreeViewExample.h"

TreeViewExample::TreeViewExample() : vbox(Gtk::ORIENTATION_VERTICAL), buttonQuit("Quit") {
  set_title("Gtk::TreeView(ListStore) example");
  set_border_width(5);
  set_default_size(400, 200);

  add(vbox);
  scrolledWindow.add(treeView);
  scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  vbox.pack_start(scrolledWindow);
  vbox.pack_start(buttonBox, Gtk::PACK_SHRINK);

  buttonBox.pack_start(buttonQuit, Gtk::PACK_SHRINK);
  buttonBox.set_border_width(5);
  buttonBox.set_layout(Gtk::BUTTONBOX_END);
  buttonQuit.signal_clicked().connect(sigc::mem_fun(*this,
                                                    &TreeViewExample::on_button_quit));

  Gtk::TreeModel::Row row = *(treeModel->append());
  row[columns.colId] = 1;
  row[columns.colName] = "Billy Bob";
  row[columns.colNumber] = 10;
  row[columns.colPercentage] = 15;

  treeView.append_column("ID",columns.colId);
  treeView.append_column("Name",columns.colName);
  treeView.append_column_numeric("Formatted number",columns.colNumber,"%010d");

  auto cell = Gtk::manage(new Gtk::CellRendererProgress);
  int cols_count = treeView.append_column("Some percentage",*cell);
  auto pColumn = treeView.get_column(cols_count - 1);


}

TreeViewExample::~TreeViewExample() {

}

void TreeViewExample::on_button_quit() {

}
