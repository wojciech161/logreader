#pragma once

#include <map>
#include <memory>
#include <gtkmm/notebook.h>
#include "LogView.hpp"
#include "TabLabel.hpp"
#include "BookmarkList.hpp"

namespace view
{
class BookmarkView;
} // namespace view
namespace controllers
{
class BookmarkController;
} // namespace controllers


namespace view
{
class LogContainer : public Gtk::Notebook
{
public:
    LogContainer(BookmarkView&, const controllers::BookmarkController&, bool);
    virtual ~LogContainer();

    LogContainer& getCurrentTab();
    LogView& getLog();
    LogView& addTab(const std::string&, bool);

private:
    void closeTab(const std::string&);
    template<typename LogTab, typename Label>
    void createTab(LogTab& logTab, Label& label);

private:
    BookmarkView& bookmarkView;
    LogView baseLog;
    const controllers::BookmarkController& bookmarkController;
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
