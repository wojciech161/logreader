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
    virtual ~BookmarkView();

    const model::Bookmark& getColumns() const;
    void update(LogView*, const Glib::RefPtr<Gtk::ListStore>&);
    Gtk::TreeModel::iterator getCurrentSelection();
    void registerActions(
        sigc::slot<void(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*)>,
        sigc::slot<void()>);

private:
    model::Bookmark columns;
    Gtk::Label boxTitle;
    Gtk::ScrolledWindow bookmarkWindow;
    Gtk::TreeView treeView;
    Gtk::Button closeBookmarkButton;
    std::vector<sigc::connection> connections;
};
} // namespace view
