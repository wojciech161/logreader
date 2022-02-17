#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include "Bookmark.hpp"

namespace controllers
{
class BookmarkController;
} // namespace controllers

namespace view
{
class BookmarkView : public Gtk::Box
{
public:
    BookmarkView(const controllers::BookmarkController&);
    virtual ~BookmarkView();

    const model::Bookmark& getColumns() const;
    void update(const Glib::RefPtr<Gtk::ListStore>&);
    Gtk::TreeModel::iterator getCurrentSelection();

private:
    model::Bookmark columns;
    Gtk::Label boxTitle;
    Gtk::ScrolledWindow bookmarkWindow;
    Gtk::TreeView treeView;
    Gtk::Button closeBookmarkButton;
    std::vector<sigc::connection> connections;
};
} // namespace view
