#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <gtkmm/notebook.h>
#include <gtksourceviewmm/buffer.h>
#include "BaseTab.hpp"
#include "TabLabel.hpp"

namespace functions
{
class Grep;
} // namespace functions 
namespace view
{
class BookmarkView;
class LogView;
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
    LogView& getCurrentLog();
    std::string getSelectedText() const;

private:
    void closeTab(const std::string&);
    void onPageChanged(Gtk::Widget*, guint);

private:
    BookmarkView& bookmarkView;
    std::map<std::string, std::unique_ptr<TabLabel>> labels;
    std::map<std::string, std::unique_ptr<BaseTab>> views;
    std::vector<std::string> paths;
};
} // namespace view
