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
} // namespace model
