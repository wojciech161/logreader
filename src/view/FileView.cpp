#include <iostream>
#include <algorithm>
#include <exception>
#include "FileView.hpp"
#include "TabLabel.hpp"
#include "Open.hpp"
#include "BookmarkView.hpp"

namespace view
{
FileView::FileView(BookmarkView& bookmarkView)
: bookmarkView{bookmarkView}
{
    set_border_width(10);
    signal_switch_page().connect(sigc::mem_fun(*this, &FileView::onPageChanged));
}

void FileView::addFile(const std::string& path) try
{
    if (views.find(path) == views.end())
    {
        functions::Open fileOpener{path};
        labels.emplace(std::make_pair(path, std::make_unique<TabLabel>(fileOpener.getName(), [this, path](){closeTab(path);})));
        views.emplace(std::make_pair(path, std::make_unique<BaseTab>(fileOpener, bookmarkView)));
        paths.push_back(path);
        append_page(*views.at(path), *labels.at(path));
        show_all_children();
    }
    else
    {
        std::cout << path << " is already opened.\n";
    }
} catch(const std::exception& e)
{
    std::cout << "Tab could not be created: " << e.what() << std::endl;
}

void FileView::addGrep(functions::Grep& grep) try
{
    views.at(paths.at(get_current_page()))->addGrep(grep);
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
}

LogView& FileView::getCurrentLog() // MAY THROW
{
    return views.at(paths.at(get_current_page()))->getCurrentTab().getLog();
}

void FileView::closeTab(const std::string& path)
{
    remove_page(*views.at(path));
    views.erase(path);
    labels.erase(path);
    paths.erase(std::remove(paths.begin(), paths.end(), path));
}

void FileView::onPageChanged(Gtk::Widget*, guint page) try
{
    views.at(paths.at(page))->updateBookmarks();
} catch(const std::exception& e)
{
    std::cout << "Unable to update bookmarks: " << e.what() << std::endl;
}
} // namespace view
