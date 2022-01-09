#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <gtkmm/notebook.h>
#include <gtksourceviewmm/buffer.h>
#include "BaseTab.hpp"
#include "TabLabel.hpp"

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
class FileView : public Gtk::Notebook
{
public:
    FileView(BookmarkView&);
    virtual ~FileView() = default;

    void addFile(const std::string&);
    void addGrep(functions::Grep&);
    void addBookmark(const std::string&);
    void addMark(const std::string&);
    void findNext(functions::Find&);
    void markWords(functions::Mark&);
    std::string getSelectedText() const;

private:
    void closeTab(const std::string&);
    void onPageChanged(Gtk::Widget*, guint);

private:
    mutable std::mutex mtx;
    BookmarkView& bookmarkView;
    std::map<std::string, std::unique_ptr<TabLabel>> labels;
    std::map<std::string, std::unique_ptr<BaseTab>> views;
    std::vector<std::string> paths;
};
} // namespace view
