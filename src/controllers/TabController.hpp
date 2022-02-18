#pragma once

#include <map>
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
} // namespace model

namespace controllers
{
class TabController
{
public:
    TabController(view::MainWindow&, model::LogList&);
    ~TabController();

    void openSingleFile();
    void removeLog(int);

private:
    bool isFileOpened(const std::string&) const;
    void cleanupParent(int);

private:
    view::MainWindow& appWindow;
    view::LogContainer& logTabs;
    model::LogList& openedLogs;
    const model::Bookmark& columns;
    std::map<int, std::string> openedFiles;
};
} // namespace controllers
