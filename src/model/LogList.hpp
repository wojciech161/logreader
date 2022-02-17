#pragma once

#include <memory>
#include <vector>

namespace model
{
class Bookmark;
class Log;
} // namespace model

namespace model
{
class LogList
{
public:
    LogList(const Bookmark&);
    ~LogList();
    LogList(const LogList&) = delete;
    LogList(LogList&&) = delete;
    LogList& operator=(const LogList&) = delete;
    LogList& operator=(LogList&&) = delete;

    void append(std::unique_ptr<Log>&&);
    Log& get(int);
    const Log& get(int) const;
    void remove(int);

private:
    const Bookmark& columns;
    std::vector<std::unique_ptr<Log>> logs;
};
} // namespace model
