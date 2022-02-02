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

namespace view
{
class LogContainer : public Gtk::Notebook
{
public:
    LogContainer(BookmarkView&, bool);
    virtual ~LogContainer();

    LogContainer& getCurrentTab();
    LogView& getLog();
    LogView& addTab(const std::string&, bool);

private:
    void closeTab(const std::string&);
    void onPageChanged(Gtk::Widget*, guint);

private:
    BookmarkView& bookmarkView;
    LogView baseLog;
    std::map<std::string, std::unique_ptr<TabLabel>> grepLabels;
    std::map<std::string, std::unique_ptr<LogContainer>> grepTabs;
    sigc::connection pageChangedConnection;
};
} // namespaceview 
