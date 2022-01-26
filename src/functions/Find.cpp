#include "Find.hpp"
#include <iostream>
#include <gtksourceviewmm/buffer.h>
#include "LogView.hpp"

namespace functions
{
Find::Find(const std::string& query, bool caseSensitive)
: query{query}
, caseSensitive{caseSensitive} {}

void Find::run(view::LogView& logView) const
{
    const auto buffer = logView.getBuffer();
    auto cursorPosition = buffer->get_insert();
    auto currentPosition = buffer->get_iter_at_mark(cursorPosition);
    Gtk::TextIter matchStart, matchEnd;
    auto flag = caseSensitive ? Gtk::TEXT_SEARCH_TEXT_ONLY : Gtk::TEXT_SEARCH_CASE_INSENSITIVE;
    if (currentPosition.forward_search(query, flag, matchStart, matchEnd))
    {
        logView.goToLine(matchStart.get_line());
        buffer->select_range(matchStart,matchEnd);
    }
    else
    {
        std::cout << query << " not found\n";
    }
}
} // namespace functions
