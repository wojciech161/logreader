#include "Log.hpp"
#include <iostream>

namespace model
{
Log::Log(int id)
: id{id}
, buffer{Gsv::Buffer::create()}
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

Glib::RefPtr<Gsv::Buffer>& Log::getBuffer()
{
    return buffer;
}

const Glib::RefPtr<Gsv::Buffer> Log::getBuffer() const
{
    return buffer;
}

int Log::getCurrentLine() const
{
    auto cursor = buffer->get_insert();
    Gtk::TextIter iter = buffer->get_iter_at_mark(cursor);
    return iter.get_line();
}
} // namespace model
