#include "BookmarkController.hpp"
#include <exception>
#include <iostream>
#include "MainWindow.hpp"
#include "LogContainer.hpp"
#include "BookmarkDialog.hpp"
#include "AddBookmark.hpp"
#include "BookmarkList.hpp"
#include "BookmarkView.hpp"

namespace controllers
{
BookmarkController::BookmarkController(view::MainWindow& appWindow)
: appWindow{appWindow}
, bookmarkView{appWindow.getBookmarkView()}
, fileView{appWindow.getFileView()}
{
    std::cout << "BookmarkController is constructed\n";
    bookmarkView.registerActions(
        sigc::mem_fun(*this, &BookmarkController::activateBookmark),
        sigc::mem_fun(*this, &BookmarkController::closeBookmark));
}

BookmarkController::~BookmarkController()
{
    std::cout << "BookmarkController is destructed\n";
}

void BookmarkController::addBookmark() const try
{
    view::BookmarkDialog dialog(appWindow);
    auto result = dialog.show();
    if (result.success)
    {
        functions::AddBookmark operation{result.name};
        operation.run(fileView.getCurrentTab().getLog());
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform bookmark: " << e.what() << std::endl;
}

void BookmarkController::closeBookmark() const try
{
    const auto& currentSelection = bookmarkView.getCurrentSelection();
    auto& currentBookmarks = fileView.getCurrentTab().getLog().getBookmarks();
    currentBookmarks.remove(currentSelection);
} catch(const std::exception& e)
{
    std::cout << "Unable to close bookmark: " << e.what() << std::endl;
}

void BookmarkController::activateBookmark(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*) const try
{
    auto& currentLog = fileView.getCurrentTab().getLog();
    auto& currentBookmarks = currentLog.getBookmarks();
    currentLog.goToLine(currentBookmarks.getBookmarkLine(path));
} catch(const std::exception& e)
{
    std::cout << "Unable to activate bookmark: " << e.what() << std::endl;
}
} // namespace controllers
