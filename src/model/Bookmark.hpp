#pragma once

#include <gtkmm/treemodel.h>

namespace model
{
struct Bookmark : public Gtk::TreeModel::ColumnRecord
{
    Bookmark();
    Gtk::TreeModelColumn<unsigned int> lineNumber;
    Gtk::TreeModelColumn<Glib::ustring> bookmarkName;
};
} // namespace model
