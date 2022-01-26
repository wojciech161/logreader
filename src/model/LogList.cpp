#include "LogList.hpp"
#include "Log.hpp"
#include <exception>

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
int LogList::append()
{
    int id = generateId();
    logs.emplace_back(std::make_unique<Log>(id));
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
