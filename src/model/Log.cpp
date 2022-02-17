#include "Log.hpp"
#include <iostream>

namespace
{
int generateId()
{
    static int id{0};
    return id++;
}
} // namespace

namespace model
{
Log::Log(const std::string& name, const Bookmark& columns)
: id{generateId()}
, name{name}
, buffer{Gsv::Buffer::create()}
, bookmarks{columns}
{
    std::cout << "Log is constructed. Id: " 
              << id << ", name: " << name << "\n";
}

Log::~Log()
{
    std::cout << "Log is destructed. Id: " 
              << id << ", name: " << name << "\n";
    buffer.reset();
}

int Log::getId() const
{
    return id;
}

const std::string& Log::getName() const
{
    return name;
}

Glib::RefPtr<Gsv::Buffer>& Log::getBuffer()
{
    return buffer;
}

const Glib::RefPtr<Gsv::Buffer> Log::getBuffer() const
{
    return buffer;
}

model::BookmarkList& Log::getBookmarks()
{
    return bookmarks;
}

const model::BookmarkList& Log::getBookmarks() const
{
    return bookmarks;
}
} // namespace model
