#include "AddBookmark.hpp"
#include "LogView.hpp"
#include "Log.hpp"

namespace functions
{
AddBookmark::AddBookmark(const std::string& name)
: bookmarkName{name}
{
}

bool AddBookmark::run(view::LogView& logView) const
{
    logView.getBookmarks().add(
    logView.getCurrentLine(), bookmarkName);
    return true;
}

bool AddBookmark::run(model::Log& log) const
{
    log.getBookmarks().add(
    log.getCurrentLine(), bookmarkName);
    return true;
}
} // namespace functions
