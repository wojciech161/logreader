#pragma once

#include <string>

namespace view
{
class LogContainer;
class MainWindow;
} // namespace view
namespace model
{
class Bookmark;
class LogList;
class Log;
} // namespace model


namespace controllers
{
class FunctionsController
{
public:
    FunctionsController(view::MainWindow&, model::LogList&);
    ~FunctionsController();

    void performGrep() const;
    void performMark() const;
    void performFind() const;

private:
    std::string getSelection(bool souldUnmark = true) const;
    model::Log& getCurrentLog() const;
    bool isGrepPresent(const model::Log&, const std::string&) const;

private:
    view::MainWindow& appWindow;
    view::LogContainer& fileView;
    model::LogList& openedLogs;
    const model::Bookmark& columns;
};
} // namespace controllers
