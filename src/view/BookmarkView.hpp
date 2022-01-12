#pragma once

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
class BookmarkView : public Gtk::ScrolledWindow
{
public:
    BookmarkView();
    virtual ~BookmarkView() = default;

    const model::BookmarkColumns& getColumns() const;
    void update(BaseTab*, const Glib::RefPtr<Gtk::ListStore>&);
    void release(BaseTab*);

private:
    void onColumnActivated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);

private:
    model::BookmarkColumns columns;
    Gtk::TreeView treeView;
    BaseTab* currentTab;
};
} // namespace view
