#include "AddBookmark.hpp"
#include "Log.hpp"

namespace functions
{
AddBookmark::AddBookmark(const std::string& name)
: bookmarkName{name} {}

bool AddBookmark::run(model::Log& log) const
{
    const auto& buffer = log.getBuffer();
    auto cursor = buffer->get_insert();
    Gtk::TextIter iter = buffer->get_iter_at_mark(cursor);
    log.getBookmarks().add(
        iter.get_line(), bookmarkName);
    return true;
}
} // namespace functions
