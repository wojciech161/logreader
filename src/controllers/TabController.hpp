#pragma once

namespace view
{
class LogContainer;
class MainWindow;
} // namespace view


namespace controllers
{
class TabController
{
public:
    TabController(view::MainWindow&);
    ~TabController();

    void openSingleFile() const;

private:
    view::MainWindow& appWindow;
    view::LogContainer& logTabs;
};
} // namespace controllers
