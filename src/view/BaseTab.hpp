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
class Find;
class Grep;
class Mark;
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
    void addBookmark(const std::string&);
    void updateBookmarks();
    void goToLine(int);
    void addMark(const std::string&);
    void findNext(functions::Find&);
    void markWords(functions::Mark&);
    std::string getSelectedText() const;
    void onBookmarkActivated(const Gtk::TreeModel::Path&);

private:
    BaseTab& getCurrentTab();
    const BaseTab& getCurrentTab() const;
    void addTab(functions::Grep&);
    void closeTab(const std::string&);
    void newBookmark(const std::string&);
    void onPageChanged(Gtk::Widget*, guint);
    void updateBookmarksView();
    void find(functions::Find&);
    void mark(functions::Mark&);
    std::string getSelection() const;

private:
    BookmarkView& bookmarkView;
    std::string name;
    LogView baseLog;
    std::map<std::string, std::unique_ptr<TabLabel>> grepLabels;
    std::map<std::string, std::unique_ptr<BaseTab>> grepTabs;
    std::vector<std::string> grepNames;
    model::BookmarkList bookmarks;
    sigc::connection pageChangedConnection;
};
} // namespaceview 
