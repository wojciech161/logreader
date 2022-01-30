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
class BaseTab : public Gtk::Notebook
{
public:
    BaseTab(BookmarkView&, bool);
    virtual ~BaseTab();

    BaseTab& getCurrentTab();
    LogView& getLog();
    LogView& addTab(const std::string&, bool);

private:
    void closeTab(const std::string&);
    void onPageChanged(Gtk::Widget*, guint);

private:
    BookmarkView& bookmarkView;
    LogView baseLog;
    std::map<std::string, std::unique_ptr<TabLabel>> grepLabels;
    std::map<std::string, std::unique_ptr<BaseTab>> grepTabs;
    std::vector<std::string> grepNames;
    sigc::connection pageChangedConnection;
};
} // namespaceview 
