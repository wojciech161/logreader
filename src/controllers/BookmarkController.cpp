#include "BookmarkController.hpp"
#include <exception>
#include <iostream>
#include "MainWindow.hpp"
#include "LogContainer.hpp"
#include "BookmarkDialog.hpp"
#include "ActivateBookmark.hpp"
#include "AddBookmark.hpp"
#include "BookmarkList.hpp"
#include "BookmarkView.hpp"
#include "LogList.hpp"
#include "Log.hpp"

namespace controllers
{
BookmarkController::BookmarkController(
    view::MainWindow& appWindow, model::LogList& openedLogs)
: appWindow{appWindow}
, openedLogs{openedLogs}
, bookmarkView{appWindow.getBookmarkView()}
, fileView{appWindow.getFileView()}
{
    std::cout << "BookmarkController is constructed\n";
}

BookmarkController::~BookmarkController()
{
    std::cout << "BookmarkController is destructed\n";
}

void BookmarkController::addBookmark() const try
{
    model::Log& currentLog = getCurrentLog();
    view::BookmarkDialog dialog(appWindow);
    auto result = dialog.show();
    if (result.success)
    {
        functions::AddBookmark operation{result.name};
        operation.run(currentLog);
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform bookmark: " << e.what() << std::endl;
}

void BookmarkController::closeBookmark() const try
{
    const auto& currentSelection = bookmarkView.getCurrentSelection();
    model::Log& currentLog = getCurrentLog();
    auto& currentBookmarks = currentLog.getBookmarks();
    currentBookmarks.remove(currentSelection);
} catch(const std::exception& e)
{
    std::cout << "Unable to close bookmark: " << e.what() << std::endl;
}

void BookmarkController::activateBookmark(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*) const try
{
    model::Log& currentLog = getCurrentLog();
    view::LogView& currentView = fileView.getCurrentTab().getLog();
    auto& currentBookmarks = currentLog.getBookmarks();
    Gtk::TextIter lineIter;
    functions::ActivateBookmark operation{currentBookmarks.getBookmarkLine(path), lineIter};
    operation.run(currentLog);
    currentView.scrollTo(lineIter);
} catch(const std::exception& e)
{
    std::cout << "Unable to activate bookmark: " << e.what() << std::endl;
}

void BookmarkController::updateView(Gtk::Widget*, guint pageNum) const try
{
    model::Log& currentLog = getCurrentLog();
    const auto& currentBookmarks = currentLog.getBookmarks();
    bookmarkView.update(currentBookmarks.getModel());
}
catch(const std::exception& e)
{
    std::cout << "Unable to update bookmark view: " << e.what() << std::endl;
}

model::Log& BookmarkController::getCurrentLog() const
{
    int currentLogId = fileView.getCurrentTab().getLog().getModelId();
    if (currentLogId == -1)
    {
        throw std::runtime_error("Can't get current log!");
    }
    return openedLogs.get(currentLogId);
}
} // namespace controllers
