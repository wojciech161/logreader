#pragma once

#include <set>
#include <string>

namespace model
{
struct Bookmark
{
    int lineNumber;
    std::string name;
};

bool operator<(const Bookmark&, const Bookmark&);
using BookmarkList = std::set<Bookmark>;
} // namespace model
