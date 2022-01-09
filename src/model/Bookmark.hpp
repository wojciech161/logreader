#pragma once

#include <gtkmm/liststore.h>
#include <gtkmm/treemodel.h>

namespace model
{
struct BookmarkColumns : public Gtk::TreeModel::ColumnRecord
{
    BookmarkColumns();
    Gtk::TreeModelColumn<unsigned int> lineNumber;
    Gtk::TreeModelColumn<Glib::ustring> bookmarkName;
};

class BookmarkList
{
public:
    BookmarkList(const BookmarkColumns&);
    ~BookmarkList();

    void add(int, const std::string&);
    int getBookmarkLine(const Gtk::TreeModel::Path&);
    const Glib::RefPtr<Gtk::ListStore>& getModel() const;

private:
    const BookmarkColumns& columns;
    Glib::RefPtr<Gtk::ListStore> bookmarks;
};
} // namespace model
