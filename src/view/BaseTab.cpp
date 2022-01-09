#include "BaseTab.hpp"
#include "LogView.hpp"
#include "Find.hpp"
#include "Grep.hpp"
#include "Mark.hpp"
#include "BookmarkView.hpp"

#include <iostream>

namespace view
{
BaseTab::BaseTab(const functions::BufferCreator& bufferCreator, BookmarkView& bookmarkView)
: bookmarkView{bookmarkView}
, name{bufferCreator.getName()}
, baseLog{bufferCreator}
{
    set_border_width(10);
    append_page(baseLog, "Base");
    show_all_children();
    signal_switch_page().connect(sigc::mem_fun(*this, &BaseTab::onPageChanged));
}

BaseTab::~BaseTab()
{
    std::cout << "~BaseTab: " << name << std::endl;
    bookmarkView.release(this);
}

void BaseTab::addGrep(functions::Grep& grep) try
{
    getCurrentTab().addTab(grep);
} catch(const std::exception& e)
{
    std::cout << "Unable to grep: " << e.what() << std::endl;
}

void BaseTab::addBookmark(const std::string& bookmarkName) try
{
    getCurrentTab().newBookmark(bookmarkName);
} catch(const std::exception& e)
{
    std::cout << "Unable to add bookmark: " << e.what() << std::endl;
}

void BaseTab::addMark(const std::string& name) try
{
    std::cout << "Add mark: " << name << std::endl;
    // getCurrentTab().newBookmark(bookmarkName);
} catch(const std::exception& e)
{
    std::cout << "Unable to add mark: " << e.what() << std::endl;
}

void BaseTab::findNext(functions::Find& operation) try
{
    getCurrentTab().find(operation);
} catch(const std::exception& e)
{
    std::cout << "Unable to perform find: " << e.what() << std::endl;
}

void BaseTab::markWords(functions::Mark& operation) try
{
    getCurrentTab().mark(operation);
} catch(const std::exception& e)
{
    std::cout << "Unable to perform mark: " << e.what() << std::endl;
}

std::string BaseTab::getSelectedText() const try
{
    return getCurrentTab().getSelection();
} catch(const std::exception& e)
{
    std::cout << "Unable to perform mark: " << e.what() << std::endl;
    return "";
}

BaseTab& BaseTab::getCurrentTab() // may throw (expected behavior)!!!
{
    if (0 == get_current_page())
    {
        return *this;
    }
    return grepTabs.at(grepNames.at(get_current_page() - 1))->getCurrentTab();
}

const BaseTab& BaseTab::getCurrentTab() const // may throw (expected behavior)!!!
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

void BaseTab::newBookmark(const std::string& bookmarkName)
{
    if (std::find_if(bookmarks.begin(), bookmarks.end(), [bookmarkName](const auto& b) {return b.name == bookmarkName;}) != bookmarks.end())
    {
        std::cout << "Bookmark " << bookmarkName << " already exists\n";
        return;
    }
    std::cout << "Add bookmark: " << bookmarkName << ", line: " << baseLog.getCurrentLine() << " for: " << name << std::endl;
    bookmarks.insert({baseLog.getCurrentLine(), bookmarkName});
    updateBookmarksView();
}

void BaseTab::onPageChanged(Gtk::Widget*, guint) try
{
    getCurrentTab().updateBookmarksView();
} catch(const std::exception& e)
{
    std::cout << "Unable to update bookmark: " << e.what() << std::endl;
}

void BaseTab::updateBookmarks() try
{
    getCurrentTab().updateBookmarksView();
} catch(const std::exception& e)
{
    std::cout << "Unable to update bookmark: " << e.what() << std::endl;
}

void BaseTab::updateBookmarksView()
{
    std::cout << "Update bookmarks view: " << name << std::endl;
    bookmarkView.update(this, bookmarks);
}

void BaseTab::goToLine(int lineNum)
{
    std::cout << name << " go to " << lineNum << std::endl;
    baseLog.goToLine(lineNum);
}

void BaseTab::find(functions::Find& operation)
{
    operation.run(baseLog);
}

void BaseTab::mark(functions::Mark& operation)
{
    operation.run(baseLog.getBuffer());
}

std::string BaseTab::getSelection() const
{
    return baseLog.getSelectedText();
}
} // namespace view
