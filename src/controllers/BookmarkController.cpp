#include "BookmarkController.hpp"
#include <exception>
#include <iostream>
#include "MainWindow.hpp"
#include "LogContainer.hpp"
#include "BookmarkDialog.hpp"
#include "AddBookmark.hpp"

namespace controllers
{
BookmarkController::BookmarkController(view::MainWindow& appWindow)
: appWindow{appWindow}
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
} // namespace controllers
