#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include "BookmarkColumns.hpp"

namespace view
{
class BaseTab;
} // namespace view

namespace view
{
class BookmarkView : public Gtk::Box
{
public:
    BookmarkView();
    virtual ~BookmarkView() = default;

    const model::BookmarkColumns& getColumns() const;
    void update(BaseTab*, const Glib::RefPtr<Gtk::ListStore>&);
    void release(BaseTab*);

private:
    void onColumnActivated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
    void onBookmarkClose();

private:
    model::BookmarkColumns columns;
    Gtk::Label boxTitle;
    Gtk::ScrolledWindow bookmarkWindow;
    Gtk::TreeView treeView;
    Gtk::Button closeBookmarkButton;
    BaseTab* currentTab;
};
} // namespace view
