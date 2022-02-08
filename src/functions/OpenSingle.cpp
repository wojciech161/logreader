#include "OpenSingle.hpp"
#include "LogView.hpp"
#include "Log.hpp"
#include <iostream>
#include <fstream>
#include "LogInserter.hpp"

namespace functions
{
OpenSingle::OpenSingle(const std::string& path)
: path{path} {}

bool OpenSingle::run(view::LogView& logView) const
{
    auto& buffer = logView.getBuffer();
    LogInserter inserter{buffer};
    std::cout << "Opening: " << path << std::endl;
    std::ifstream file(path);
    if (not file.is_open())
    {
        std::cout << "Could not open file!\n";
        return false;
    }
    std::string line;
    while (std::getline(file, line))
    {
        inserter.addLine(line + "\n");
    }
    buffer->place_cursor(buffer->get_iter_at_line(0));
    return true;
}

bool OpenSingle::run(model::Log& log) const
{
    auto& buffer = log.getBuffer();
    LogInserter inserter{buffer};
    std::cout << "Opening: " << path << std::endl;
    std::ifstream file(path);
    if (not file.is_open())
    {
        std::cout << "Could not open file!\n";
        return false;
    }
    std::string line;
    while (std::getline(file, line))
    {
        inserter.addLine(line + "\n");
    }
    buffer->place_cursor(buffer->get_iter_at_line(0));
    return true;
}
} // namespace functions
