#pragma once

#include <map>
#include <memory>
#include <gtkmm/notebook.h>
#include "BufferCreator.hpp"
#include "LogView.hpp"
#include "TabLabel.hpp"
#include "BookmarkList.hpp"

namespace functions
{
class Grep;
} // namespace functions
namespace view
{
class BookmarkView;
} // namespace view

namespace view
{
class BaseTab : public Gtk::Notebook
{
public:
    BaseTab(const functions::BufferCreator&, BookmarkView&);
    virtual ~BaseTab();

    void addGrep(functions::Grep&);
    void updateBookmarks();
    BaseTab& getCurrentTab();
    LogView& getLog();

private:
    void addTab(functions::Grep&);
    void closeTab(const std::string&);
    void onPageChanged(Gtk::Widget*, guint);

private:
    BookmarkView& bookmarkView;
    std::string name;
    LogView baseLog;
    std::map<std::string, std::unique_ptr<TabLabel>> grepLabels;
    std::map<std::string, std::unique_ptr<BaseTab>> grepTabs;
    std::vector<std::string> grepNames;
    sigc::connection pageChangedConnection;
};
} // namespaceview 
