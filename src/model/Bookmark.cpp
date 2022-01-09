#include "Bookmark.hpp"

namespace model
{
bool operator<(const Bookmark& l, const Bookmark& r)
{
    return l.lineNumber < r.lineNumber;
}
} // namespace model
