#include "BaseTab.hpp"
#include "LogView.hpp"
#include "Grep.hpp"
#include "BookmarkView.hpp"

#include <iostream>

namespace view
{
BaseTab::BaseTab(const functions::BufferCreator& bufferCreator, BookmarkView& bookmarkView)
: bookmarkView{bookmarkView}
, name{bufferCreator.getName()}
, baseLog{bufferCreator, bookmarkView}
{
    set_border_width(10);
    append_page(baseLog, "Base");
    show_all_children();
    pageChangedConnection = 
        signal_switch_page().connect(sigc::mem_fun(*this, &BaseTab::onPageChanged));
}

BaseTab::~BaseTab()
{
    std::cout << "~BaseTab: " << name << std::endl;
    pageChangedConnection.disconnect();
}

void BaseTab::addGrep(functions::Grep& grep) try
{
    getCurrentTab().addTab(grep);
} catch(const std::exception& e)
{
    std::cout << "Unable to grep: " << e.what() << std::endl;
}

BaseTab& BaseTab::getCurrentTab() // may throw (expected behavior)!!!
{
    if (0 == get_current_page())
    {
        return *this;
    }
    return grepTabs.at(grepNames.at(get_current_page() - 1))->getCurrentTab();
}

void BaseTab::addTab(functions::Grep& grep)
{
    std::string grepName{grep.getName()};
    if (grepTabs.find(grepName) != grepTabs.end())
    {
        std::cout << "Grep already exists. Skipping.\n";
        return;
    }
    grep.setBase(baseLog.getBuffer());
    grepLabels.emplace(std::make_pair(grepName, std::make_unique<TabLabel>(grepName, [this, grepName](){closeTab(grepName);})));
    grepTabs.emplace(std::make_pair(grepName, std::make_unique<BaseTab>(grep, bookmarkView)));
    grepNames.push_back(grepName);
    append_page(*grepTabs.at(grepName), *grepLabels.at(grepName));
    show_all_children();
}

void BaseTab::closeTab(const std::string& tabName)
{
    remove_page(*grepTabs.at(tabName));
    grepTabs.erase(tabName);
    grepLabels.erase(tabName);
    grepNames.erase(std::remove(grepNames.begin(), grepNames.end(), tabName));
}

void BaseTab::onPageChanged(Gtk::Widget*, guint) try
{
    getCurrentTab().updateBookmarks();
} catch(const std::exception& e)
{
    std::cout << "Unable to update bookmark: " << e.what() << std::endl;
}

void BaseTab::updateBookmarks() try
{
    getCurrentTab().getLog().updateBookmarksView();
} catch(const std::exception& e)
{
    std::cout << "Unable to update bookmark: " << e.what() << std::endl;
}

LogView& BaseTab::getLog()
{
    return baseLog;
}
} // namespace view
