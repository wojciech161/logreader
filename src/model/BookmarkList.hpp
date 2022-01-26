#pragma once

#include <gtkmm/liststore.h>
#include "Bookmark.hpp"

namespace model
{
class BookmarkList
{
public:
    BookmarkList(const Bookmark&);
    ~BookmarkList();

    void add(int, const std::string&);
    void remove(const Gtk::TreeModel::iterator&);
    int getBookmarkLine(const Gtk::TreeModel::Path&);
    const Glib::RefPtr<Gtk::ListStore>& getModel() const;

private:
    const Bookmark& columns;
    Glib::RefPtr<Gtk::ListStore> bookmarks;
};
} // namespace model
