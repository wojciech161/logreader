#include "ActivateBookmark.hpp"
#include "Log.hpp"

namespace functions
{
ActivateBookmark::ActivateBookmark(int lineNumber, Gtk::TextIter& iterAtLine)
: lineNumber{lineNumber}
, iterAtLine{iterAtLine}
{
}

bool ActivateBookmark::run(model::Log& log) const
{
    auto& buffer = log.getBuffer();
    iterAtLine = buffer->get_iter_at_line(lineNumber);
    buffer->place_cursor(iterAtLine);
    return true;
}
} // namespace functions
