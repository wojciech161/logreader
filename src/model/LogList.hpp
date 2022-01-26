#pragma once

#include <memory>
#include <vector>

namespace model
{
class Log;
} // namespace model


namespace model
{
class LogList
{
public:
    LogList() = default;
    ~LogList() = default;
    LogList(const LogList&) = delete;
    LogList(LogList&&) = delete;
    LogList& operator=(const LogList&) = delete;
    LogList& operator=(LogList&&) = delete;

    int append();
    Log& get(int);
    void remove(int);

private:
    std::vector<std::unique_ptr<Log>> logs;
};
} // namespace model
