#pragma once

#include <gtkmm/treemodel.h>
#include <gtkmm/treeviewcolumn.h>

namespace view
{
class BookmarkView;
class LogContainer;
class MainWindow;
} // namespace view


namespace controllers
{
class BookmarkController
{
public:
    BookmarkController(view::MainWindow&);
    ~BookmarkController();

    void addBookmark() const;
    void closeBookmark() const;
    void activateBookmark(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*) const;
    void updateView(Gtk::Widget*, guint) const;

private:
    view::MainWindow& appWindow;
    view::BookmarkView& bookmarkView;
    view::LogContainer& fileView;
};
} // namespace controllers
