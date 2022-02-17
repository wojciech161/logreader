#include "LogList.hpp"
#include <exception>
#include <iostream>
#include "Log.hpp"

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

void LogList::append(std::unique_ptr<Log>&& log)
{
    logs.emplace_back(std::move(log));
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

const Log& LogList::get(int id) const
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
    logs.erase(std::remove_if(
        logs.begin(), logs.end(), [id](const auto& log){return log->getId() == id;}), logs.end());
}
} // namespace model
