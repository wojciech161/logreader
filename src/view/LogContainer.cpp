#include "LogContainer.hpp"
#include "LogView.hpp"
#include "BookmarkController.hpp"
#include "Log.hpp"

#include <iostream>

namespace view
{
LogContainer::LogContainer(
    const controllers::BookmarkController& bookmarkController,
    controllers::TabController& tabController)
: baseLog{tabController}
, bookmarkController{bookmarkController}
, tabController{tabController}
{
    std::cout << "Top LogContainer is constructed\n";
    set_border_width(10);
    set_scrollable(true);
    pageChangedConnection = signal_switch_page().connect(
        sigc::mem_fun(bookmarkController, &controllers::BookmarkController::updateView));
    show_all_children();
}

LogContainer::LogContainer(
    const model::Log& log,
    const controllers::BookmarkController& bookmarkController,
    controllers::TabController& tabController)
: baseLog{log, tabController}
, bookmarkController{bookmarkController}
, tabController{tabController}
{
    std::cout << "LogContainer is constructed for log: " << log.getId() << "\n";
    set_border_width(10);
    set_scrollable(true);
    pageChangedConnection = signal_switch_page().connect(
        sigc::mem_fun(bookmarkController, &controllers::BookmarkController::updateView));
    createTab(baseLog, "Base");
    show_all_children();
}

LogContainer::~LogContainer()
{
    std::cout << "LogContainer is destructed\n";
    pageChangedConnection.disconnect();
}

LogContainer& LogContainer::getCurrentTab() // may throw (expected behavior)!!!
{
    auto* currentTab = get_nth_page(get_current_page());
    if (currentTab)
    {
        if ("Base" == get_tab_label_text(*currentTab))
        {
            return *this;
        }
        return dynamic_cast<LogContainer*>(currentTab)->getCurrentTab();
    }
    else
    {
        throw std::runtime_error("Could not get a tab!");
    }
}

LogView& LogContainer::addTab(const model::Log& log)
{
    grepLabels.emplace(std::make_pair(log.getName(), std::make_unique<TabLabel>(
        log.getName(), [this, name=log.getName()](){closeTab(name);})));
    grepTabs.emplace(std::make_pair(log.getName(), std::make_unique<LogContainer>(
        log, bookmarkController, tabController)));
    createTab(*grepTabs.at(log.getName()), *grepLabels.at(log.getName()));
    show_all_children();
    return grepTabs[log.getName()]->getLog();
}

void LogContainer::closeTab(const std::string& tabName)
{
    remove_page(*grepTabs.at(tabName));
    grepTabs.erase(tabName);
    grepLabels.erase(tabName);
}

LogView& LogContainer::getLog()
{
    return baseLog;
}
} // namespace view
