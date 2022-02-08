#include "LogList.hpp"
#include "Log.hpp"
#include <exception>
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
LogList::LogList(const Bookmark& columns)
: columns{columns}
{
    std::cout << "LogList is constructed\n";
}

LogList::~LogList()
{
    std::cout << "LogList is destructed\n";
}

int LogList::append(const std::string& name)
{
    int id = generateId();
    logs.emplace_back(std::make_unique<Log>(id, name, columns));
    return id;
}

Log& LogList::get(int id)
{
    auto log =
        std::find_if(logs.begin(), logs.end(), [id](const auto& log){return log->getId() == id;});
    if (log != logs.end())
    {
        return **log;
    }
    throw std::runtime_error("Log with id: " + std::to_string(id) + " not available");
}

void LogList::remove(int id)
{
    std::remove_if(logs.begin(), logs.end(), [id](const auto& log){return log->getId() == id;});
}
} // namespace model
