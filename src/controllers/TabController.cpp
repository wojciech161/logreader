#include "TabController.hpp"
#include <exception>
#include <iostream>
#include "LogContainer.hpp"
#include "MainWindow.hpp"
#include "FileChooser.hpp"
#include "OpenSingle.hpp"
#include "NameCreator.hpp"
#include "LogList.hpp"
#include "Log.hpp"
#include "BookmarkView.hpp"

namespace
{
constexpr int NO_PARENT{-1};
} // namespace

namespace controllers
{
TabController::TabController(view::MainWindow& appWindow, model::LogList& openedLogs)
: appWindow{appWindow}
, logTabs{appWindow.getFileView()}
, openedLogs{openedLogs}
, columns{appWindow.getBookmarkView().getColumns()}
{
    std::cout << "TabController is constructed\n";
}

TabController::~TabController()
{
    std::cout << "TabController is destructed\n";
}

void TabController::openSingleFile() try
{
    view::FileChooser fileChooser(appWindow);
    std::string path = fileChooser.getFilepath();
    if (not path.empty() and not isFileOpened(path))
    {
        auto newLog{std::make_unique<model::Log>(functions::createName(path), columns, NO_PARENT)};
        functions::OpenSingle operation{path};
        if (operation.run(*newLog))
        {
            int newLogId{newLog->getId()};
            openedLogs.append(std::move(newLog));
            logTabs.addTab(openedLogs.get(newLogId));
            openedFiles.insert(std::make_pair(newLogId, path));
        }
    }
    else
    {
        std::cout << "Path is empty or file exists\n";
    }
} catch (const std::exception& e)
{
    std::cout << "Open single file failed: " << e.what() << std::endl;
}

void TabController::removeLog(int id)
{
    cleanupParent(id);
    openedLogs.remove(id);
}

bool TabController::isFileOpened(const std::string& path) const
{
    return std::find_if(openedFiles.begin(), openedFiles.end(), [path](const auto& item){
        return item.second == path; }) != openedFiles.end();
}

void TabController::cleanupParent(int id) try
{
    int parentId = openedLogs.get(id).getParentId();
    if (parentId != NO_PARENT)
    {
        openedLogs.get(parentId).removeChild(id);
    }
    else
    {
        openedFiles.erase(id);
    }
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}
} // namespace controllers
