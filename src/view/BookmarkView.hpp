#pragma once

#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include "Bookmark.hpp"

namespace view
{
class BaseTab;
} // namespace view

namespace view
{
class BookmarkView : public Gtk::ScrolledWindow
{
    class BookmarkColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
        BookmarkColumns() { add(lineNumber); add(bookmarkName);}

        Gtk::TreeModelColumn<unsigned int> lineNumber;
        Gtk::TreeModelColumn<Glib::ustring> bookmarkName;
    };
public:
    BookmarkView();
    virtual ~BookmarkView() = default;

    void update(BaseTab*, const model::BookmarkList&);
    void release(BaseTab*);
    void clear();

private:
    void onColumnActivated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);

private:
    BookmarkColumns columns;
    Gtk::TreeView treeView;
    Glib::RefPtr<Gtk::ListStore> refTreeModel;
    BaseTab* currentTab;
};
} // namespace view
