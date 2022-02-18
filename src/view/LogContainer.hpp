#pragma once

#include <map>
#include <memory>
#include <gtkmm/notebook.h>
#include "LogView.hpp"
#include "TabLabel.hpp"
#include "BookmarkList.hpp"

namespace controllers
{
class BookmarkController;
class TabController;
} // namespace controllers
namespace model
{
class Log;
} // namespace model


namespace view
{
class LogContainer : public Gtk::Notebook
{
public:
    LogContainer(const controllers::BookmarkController&, controllers::TabController&);
    LogContainer(const model::Log&, const controllers::BookmarkController&, controllers::TabController&);
    virtual ~LogContainer();

    LogContainer& getCurrentTab();
    LogView& getLog();
    LogView& addTab(const model::Log&);

private:
    void closeTab(const std::string&);
    template<typename LogTab, typename Label>
    void createTab(LogTab& logTab, Label& label);

private:
    LogView baseLog;
    const controllers::BookmarkController& bookmarkController;
    controllers::TabController& tabController;
    std::map<std::string, std::unique_ptr<TabLabel>> grepLabels;
    std::map<std::string, std::unique_ptr<LogContainer>> grepTabs;
    sigc::connection pageChangedConnection;
};

template<typename LogTab, typename Label>
void LogContainer::createTab(LogTab& logTab, Label& label)
{
    int newTab = append_page(logTab, label);
    if (newTab != -1)
    {
        set_current_page(newTab);
        set_tab_reorderable(*get_nth_page(newTab));
    }
}
} // namespaceview 
