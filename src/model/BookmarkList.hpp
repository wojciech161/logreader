#pragma once

#include <gtkmm/liststore.h>
#include "BookmarkColumns.hpp"

namespace model
{
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
