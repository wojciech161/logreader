#include "Log.hpp"
#include <iostream>

namespace model
{
Log::Log(int id, const std::string& name, const Bookmark& columns)
: id{id}
, name{name}
, buffer{Gsv::Buffer::create()}
, bookmarks{columns}
{
    std::cout << "Log is constructed\n";
}

Log::~Log()
{
    std::cout << "Log is destructed\n";
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

int Log::getCurrentLine() const
{
    auto cursor = buffer->get_insert();
    Gtk::TextIter iter = buffer->get_iter_at_mark(cursor);
    return iter.get_line();
}
} // namespace model
