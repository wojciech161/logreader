#include "Find.hpp"
#include <iostream>
#include <gtksourceviewmm/buffer.h>
#include "LogView.hpp"

namespace functions
{
Find::Find(const std::string& query, bool caseSensitive, Gtk::TextIter& iterAtFound)
: query{query}
, caseSensitive{caseSensitive}
, iterAtFound{iterAtFound} {}

bool Find::run(view::LogView& logView) const
{
    const auto buffer = logView.getBuffer();
    auto cursorPosition = buffer->get_insert();
    auto currentPosition = buffer->get_iter_at_mark(cursorPosition);
    Gtk::TextIter matchStart, matchEnd;
    auto flag = caseSensitive ? Gtk::TEXT_SEARCH_TEXT_ONLY : Gtk::TEXT_SEARCH_CASE_INSENSITIVE;
    if (currentPosition.forward_search(query, flag, matchStart, matchEnd))
    {
        buffer->place_cursor(matchStart);
        buffer->select_range(matchStart,matchEnd);
        iterAtFound = matchStart;
        return true;
    }
    else
    {
        std::cout << query << " not found\n";
    }
    return false;
}
} // namespace functions
