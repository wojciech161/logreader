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
Log::Log(const std::string& name, const Bookmark& columns, int parentId)
: id{generateId()}
, name{name}
, parentId{parentId}
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

void Log::addChild(int childId)
{
    std::cout << "Log (id: " << id << ") add child: " << childId << std::endl;
    children.push_back(childId);
}
void Log::removeChild(int childId)
{
    std::cout << "Log (id: " << id << ") remove child: " << childId << std::endl;
    children.erase(std::remove(children.begin(), children.end(), childId), children.end());
}

int Log::getParentId() const
{
    return parentId;
}

const std::vector<int>& Log::getChildren() const
{
    return children;
}
} // namespace model
