#pragma once

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

    void openSingleFile() const;
    void removeLog(int) const;

private:
    view::MainWindow& appWindow;
    view::LogContainer& logTabs;
    model::LogList& openedLogs;
    const model::Bookmark& columns;
};
} // namespace controllers
