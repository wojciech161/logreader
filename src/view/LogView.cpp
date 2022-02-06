#include "LogView.hpp"
#include <gtksourceviewmm/buffer.h>
#include "BookmarkView.hpp"

#include <iostream> // temporary

namespace view
{
LogView::LogView(BookmarkView& bookmarkView)
: buffer{Gsv::Buffer::create()}
, bookmarks{bookmarkView.getColumns()}
{
    std::cout << "LogView is constructed\n";
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    add(textView);
    textView.set_editable(false);
    textView.set_cursor_visible(true);
    textView.set_show_line_numbers(true);
    textView.set_highlight_current_line(true);
    textView.set_source_buffer(buffer);
    textView.show();
}

LogView::~LogView()
{
    std::cout << "LogView is destructed\n";
}

const Glib::RefPtr<Gsv::Buffer>& LogView::getBuffer() const
{
    return buffer;
}

Glib::RefPtr<Gsv::Buffer>& LogView::getBuffer()
{
    return buffer;
}

int LogView::getCurrentLine() const
{
    auto cursor = buffer->get_insert();
    Gtk::TextIter iter = buffer->get_iter_at_mark(cursor);
    return iter.get_line();
}

model::BookmarkList& LogView::getBookmarks()
{
    return bookmarks;
}

void LogView::goToLine(int lineNum)
{
    auto iter = buffer->get_iter_at_line(lineNum);
    buffer->place_cursor(iter);
    textView.scroll_to(iter);
}
} // namespace view
