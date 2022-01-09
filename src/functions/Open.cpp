#include "Open.hpp"
#include <iostream>
#include <fstream>
#include "LogInserter.hpp"

namespace functions
{
Open::Open(const std::string& path)
: path{path}
{

}

Glib::RefPtr<Gsv::Buffer> Open::createBuffer() const
{
    Glib::RefPtr<Gsv::Buffer> buffer{Gsv::Buffer::create()};
    LogInserter inserter{buffer};
    std::cout << "Opening: " << path << std::endl;
    std::ifstream file(path);
    if (not file.is_open())
    {
        std::cout << "Could not open file!\n";
        return buffer;
    }
    std::string line;
    while (std::getline(file, line))
    {
        inserter.addLine(line + "\n");
    }
    buffer->place_cursor(buffer->get_iter_at_line(0));
    return buffer;
}

std::string Open::getName() const
{
    auto const pos = path.find_last_of('/');
    const auto leaf = path.substr(pos+1);
    return leaf;
}
} // namespace functions
