#include "LogView.hpp"
#include <gtksourceviewmm/buffer.h>
#include "BookmarkView.hpp"

#include <iostream> // temporary

namespace view
{
LogView::LogView(const functions::BufferCreator& bufferCreator, BookmarkView& bookmarkView)
: buffer{bufferCreator.createBuffer()}
, bookmarkView{bookmarkView}
, bookmarks{bookmarkView.getColumns()}
{
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
    bookmarkView.release(this);
}

const Glib::RefPtr<Gsv::Buffer>& LogView::getBuffer() const
{
    return buffer;
}

int LogView::getCurrentLine() const
{
    auto cursor = buffer->get_insert();
    Gtk::TextIter iter = buffer->get_iter_at_mark(cursor);
    return iter.get_line();
}

void LogView::goToLine(int lineNum)
{
    auto iter = buffer->get_iter_at_line(lineNum);
    buffer->place_cursor(iter);
    textView.scroll_to(iter);
}

std::string LogView::getSelectedText() const
{
    Gtk::TextIter selectionStart, selectionEnd;
    if (buffer->get_selection_bounds(selectionStart, selectionEnd))
    {
        buffer->place_cursor(selectionEnd);
        return buffer->get_text(selectionStart, selectionEnd);
    }
    return "";
}

void LogView::onBookmarkActivated(const Gtk::TreeModel::Path& path)
{
    int line = bookmarks.getBookmarkLine(path);
    if (line > 0)
    {
        goToLine(line);
    }
}

void LogView::deleteBookmark(const Gtk::TreeModel::iterator& iter)
{
    bookmarks.remove(iter);
}

void LogView::newBookmark(const std::string& bookmarkName)
{
    std::cout << "Add bookmark: " << bookmarkName << ", line: " << getCurrentLine() << std::endl;
    bookmarks.add(getCurrentLine(), bookmarkName);
}

void LogView::updateBookmarksView()
{
    std::cout << "Update bookmarks view\n";
    bookmarkView.update(this, bookmarks.getModel());
}
} // namespace view
