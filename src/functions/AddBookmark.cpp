#include "AddBookmark.hpp"
#include "LogView.hpp"

namespace functions
{
AddBookmark::AddBookmark(const std::string& name)
: bookmarkName{name}
{
}

void AddBookmark::run(view::LogView& logView) const
{
    logView.newBookmark(bookmarkName);
}
} // namespace functions
