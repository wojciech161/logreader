#pragma once

#include <gtkmm/treemodel.h>

namespace model
{
struct BookmarkColumns : public Gtk::TreeModel::ColumnRecord
{
    BookmarkColumns();
    Gtk::TreeModelColumn<unsigned int> lineNumber;
    Gtk::TreeModelColumn<Glib::ustring> bookmarkName;
};
} // namespace model
