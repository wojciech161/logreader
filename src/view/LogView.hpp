#pragma once

#include <string>

#include <gtkmm/scrolledwindow.h>
#include <gtksourceviewmm/buffer.h>
#include <gtksourceviewmm/view.h>
#include "BufferCreator.hpp"
#include "BookmarkList.hpp"

namespace view
{
class BookmarkView;
} // namespace view

namespace view
{
class LogView : public Gtk::ScrolledWindow
{
public:
    LogView(const functions::BufferCreator&, BookmarkView&);
    virtual ~LogView();

    const Glib::RefPtr<Gsv::Buffer>& getBuffer() const;
    int getCurrentLine() const;
    void goToLine(int);
    void onBookmarkActivated(const Gtk::TreeModel::Path&);
    void deleteBookmark(const Gtk::TreeModel::iterator&);
    void newBookmark(const std::string&);
    void updateBookmarksView();

private:
    Gsv::View textView;
    Glib::RefPtr<Gsv::Buffer> buffer;
    BookmarkView& bookmarkView;
    model::BookmarkList bookmarks;
};
} // namespace view
