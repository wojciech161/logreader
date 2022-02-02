#include "LogContainer.hpp"
#include "LogView.hpp"
#include "BookmarkView.hpp"

#include <iostream>

namespace view
{
LogContainer::LogContainer(BookmarkView& bookmarkView, bool createBase)
: bookmarkView{bookmarkView}
, baseLog{bookmarkView}
{
    set_border_width(10);
    pageChangedConnection = 
        signal_switch_page().connect(sigc::mem_fun(*this, &LogContainer::onPageChanged));
    if (createBase)
    {
        append_page(baseLog, "Base");
    }
    show_all_children();
}

LogContainer::~LogContainer()
{
    std::cout << "~LogContainer()\n";
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

LogView& LogContainer::addTab(const std::string& name, bool createBase)
{
    // if (grepTabs.find(name) != grepTabs.end()) // Should be moved to model
    // {
    //     std::cout << "Grep already exists. Skipping.\n";
    //     return;
    // }
    grepLabels.emplace(std::make_pair(name, std::make_unique<TabLabel>(name, [this, name](){closeTab(name);})));
    grepTabs.emplace(std::make_pair(name, std::make_unique<LogContainer>(bookmarkView, createBase)));
    int newTab = append_page(*grepTabs.at(name), *grepLabels.at(name));
    show_all_children();
    if (newTab != -1)
    {
        set_current_page(newTab);
    }
    return grepTabs[name]->getLog();
}

void LogContainer::closeTab(const std::string& tabName)
{
    remove_page(*grepTabs.at(tabName));
    grepTabs.erase(tabName);
    grepLabels.erase(tabName);
}

void LogContainer::onPageChanged(Gtk::Widget* currentTab, guint) try
{
    auto& logView = getCurrentTab().getLog();
    const auto& bookmarks = logView.getBookmarks();
    bookmarkView.update(&logView, bookmarks.getModel());
} catch(const std::exception& e)
{
    std::cout << "Unable to update bookmark: " << e.what() << std::endl;
}

LogView& LogContainer::getLog()
{
    return baseLog;
}
} // namespace view
