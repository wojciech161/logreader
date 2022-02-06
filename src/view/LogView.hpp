#pragma once

#include <string>

#include <gtkmm/scrolledwindow.h>
#include <gtksourceviewmm/buffer.h>
#include <gtksourceviewmm/view.h>
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
    LogView(BookmarkView&);
    virtual ~LogView();

    const Glib::RefPtr<Gsv::Buffer>& getBuffer() const;
    Glib::RefPtr<Gsv::Buffer>& getBuffer();
    model::BookmarkList& getBookmarks();
    int getCurrentLine() const;
    void goToLine(int);

private:
    Gsv::View textView;
    Glib::RefPtr<Gsv::Buffer> buffer;
    model::BookmarkList bookmarks;
};
} // namespace view
