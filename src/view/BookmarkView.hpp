#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include "Bookmark.hpp"

namespace view
{
class LogView;
} // namespace view

namespace view
{
class BookmarkView : public Gtk::Box
{
public:
    BookmarkView();
    virtual ~BookmarkView() = default;

    const model::Bookmark& getColumns() const;
    void update(LogView*, const Glib::RefPtr<Gtk::ListStore>&);
    void release(LogView*);

private:
    void onColumnActivated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
    void onBookmarkClose();

private:
    model::Bookmark columns;
    Gtk::Label boxTitle;
    Gtk::ScrolledWindow bookmarkWindow;
    Gtk::TreeView treeView;
    Gtk::Button closeBookmarkButton;
    LogView* currentLog;
};
} // namespace view
