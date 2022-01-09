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
        {
            std::lock_guard lock{mtx};
            labels.emplace(std::make_pair(path, std::make_unique<TabLabel>(fileOpener.getName(), [this, path](){closeTab(path);})));
            views.emplace(std::make_pair(path, std::make_unique<BaseTab>(fileOpener, bookmarkView)));
            paths.push_back(path);
        }
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
    std::lock_guard lock{mtx};
    views.at(paths.at(get_current_page()))->addGrep(grep);
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
}

void FileView::addBookmark(const std::string& name) try
{
    std::lock_guard lock{mtx};
    views.at(paths.at(get_current_page()))->addBookmark(name);
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
}

void FileView::addMark(const std::string& word) try
{
    std::lock_guard lock{mtx};
    views.at(paths.at(get_current_page()))->addMark(word);
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
}

void FileView::findNext(functions::Find& operation) try
{
    std::lock_guard lock{mtx};
    views.at(paths.at(get_current_page()))->findNext(operation);
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
}

void FileView::markWords(functions::Mark& operation) try
{
    std::lock_guard lock{mtx};
    views.at(paths.at(get_current_page()))->markWords(operation);
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
}

std::string FileView::getSelectedText() const try
{
    std::lock_guard lock{mtx};
    return views.at(paths.at(get_current_page()))->getSelectedText();
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
    return "";
}

void FileView::closeTab(const std::string& path)
{
    remove_page(*views.at(path));
    std::lock_guard lock{mtx};
    views.erase(path);
    labels.erase(path);
    paths.erase(std::remove(paths.begin(), paths.end(), path));
}

void FileView::onPageChanged(Gtk::Widget*, guint page) try
{
    std::lock_guard lock{mtx};
    views.at(paths.at(page))->updateBookmarks();
} catch(const std::exception& e)
{
    std::cout << "Unable to update bookmarks: " << e.what() << std::endl;
}
} // namespace view
