//
// Created by rick on 2018/1/24.
//

#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType *cobject,
                       const Glib::RefPtr<Gtk::Builder> &refBuilder) : Gtk::ApplicationWindow{cobject},
                                                                       _refBuilder{refBuilder} {
  _refBuilder->get_widget("stack", _stack);

  _refBuilder->get_widget("search", _search);
  _refBuilder->get_widget("searchbar", _searchbar);
  _refBuilder->get_widget("searchentry", _searchentry);
  _refBuilder->get_widget("gears", _gears);
  _refBuilder->get_widget("sidebar", _sidebar);
  _refBuilder->get_widget("words", _words);

  // Bind Settings
  _settings = Gio::Settings::create("org.gtkmm.exampleapp");
  _settings->bind("transition", _stack->property_transition_type());
  _settings->bind("show-words",_sidebar->property_reveal_child());

  // Bind properties
  _prop_binding = Glib::Binding::bind_property(_search->property_active(),
                                               _searchbar->property_search_mode_enabled(),
                                               Glib::BINDING_BIDIRECTIONAL);

  // Connect signal handlers
  _searchentry->signal_search_changed().connect(sigc::mem_fun(*this, &MainWindow::on_search_text_changed));
  _stack->property_visible_child().signal_changed().connect(
    sigc::mem_fun(*this, &MainWindow::on_visible_child_changed));
  _sidebar->property_reveal_child().signal_changed().connect(
    sigc::mem_fun(*this, &MainWindow::on_reveal_child_changed)
  );

  // Connect the menu to the MenuButton _gears
  auto menu_builder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/gears_menu.glade");
  auto object = menu_builder->get_object("menu");
  auto menu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(object);
  _gears->set_menu_model(menu);
  add_action(_settings->create_action("show-words"));

}

void MainWindow::open_file_view(const Glib::RefPtr<Gio::File> &file) {
  const auto basename = file->get_basename();
  auto scrolled = Gtk::manage(new Gtk::ScrolledWindow);
  scrolled->set_hexpand(true);
  scrolled->set_vexpand(true);
  scrolled->show();

  auto view = Gtk::manage(new Gtk::TextView);
  view->set_editable(false);
  view->set_cursor_visible(false);
  view->show();

  scrolled->add(*view);
  _stack->add(*scrolled, basename, basename);

  auto buffer = view->get_buffer();
  try {
    char *contents = nullptr;
    gsize length = -1;
    file->load_contents(contents, length);
    buffer->set_text(contents, contents + length);
    g_free(contents);
  } catch (const Glib::Error &ex) {
    std::cerr << "open_file_view(" << file->get_parse_name() << ")\n" << ex.what() << std::endl;
  }

  auto tag = buffer->create_tag();
  _settings->bind("font", tag->property_font());
  buffer->apply_tag(tag, buffer->begin(), buffer->end());

  _search->set_sensitive(true);
  update_words();
}

MainWindow *MainWindow::create() {
  auto refBuilder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/window.glade");
  MainWindow *window = nullptr;
  refBuilder->get_widget_derived("app_window", window);
  if (!window)
    throw std::runtime_error("No \"app_window\" object in window.ui");
  return window;
}

void MainWindow::on_search_text_changed() {
  const auto text = _searchentry->get_text();
  if (text.empty())
    return;

  auto tab = dynamic_cast<Gtk::ScrolledWindow *>(_stack->get_visible_child());
  auto view = dynamic_cast<Gtk::TextView *>(tab->get_child());

  //Very simple search
  auto buffer = view->get_buffer();
  Gtk::TextIter match_start;
  Gtk::TextIter match_end;
  if (buffer->begin().forward_search(text, Gtk::TEXT_SEARCH_CASE_INSENSITIVE,
                                     match_start, match_end)) {
    buffer->select_range(match_start, match_end);
    view->scroll_to(match_start);
  }

}

void MainWindow::on_visible_child_changed() {
  _searchbar->set_search_mode(false);
  update_words();
}

void MainWindow::update_words() {
  auto tab = dynamic_cast<Gtk::ScrolledWindow *>(_stack->get_visible_child());
  auto view = dynamic_cast<Gtk::TextView *>(tab->get_child());

  auto buffer = view->get_buffer();

  // Find all words in the text buffer.
  std::set<Glib::ustring> words;
  auto start = buffer->begin();
  Gtk::TextIter end;
  while (start) {
    while (start && !start.starts_word())
      ++start;

    if (!start)
      break;

    end = start;
    end.forward_word_end();
    if (start == end)
      break;

    auto word = buffer->get_text(start, end, false);
    words.insert(word.lowercase());
    start = end;
  }

  // Remove old children from the ListBox.
  auto old_children = _words->get_children();
  for (auto child:old_children) {
    _words->remove(*child);
    delete child;
  }

  // Add new child buttons, one per unique word.
  for (const auto &word:words) {
    auto row = Gtk::manage(new Gtk::Button(word));
    row->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
                                                           &MainWindow::on_find_word), row));
    row->show();
    _words->add(*row);
  }

}

void MainWindow::on_find_word(const Gtk::Button *button) {
  _searchentry->set_text(button->get_label());
}

void MainWindow::on_reveal_child_changed() {
  update_words();
}
