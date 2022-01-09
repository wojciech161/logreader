#include "LogView.hpp"
#include <gtksourceviewmm/buffer.h>

#include <iostream> // temporary

namespace view
{
LogView::LogView(const functions::BufferCreator& bufferCreator)
: buffer{bufferCreator.createBuffer()}
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
} // namespace view
