#pragma once

#include <memory>
#include <string>
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

    int append(const std::string&);
    Log& get(int);
    void remove(int);

private:
    const Bookmark& columns;
    std::vector<std::unique_ptr<Log>> logs;
};
} // namespace model
