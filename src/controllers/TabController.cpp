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

void TabController::openSingleFile() const try
{
    view::FileChooser fileChooser(appWindow);
    std::string path = fileChooser.getFilepath();
    if (not path.empty())
    {
        auto newLog{std::make_unique<model::Log>(functions::createName(path), columns, NO_PARENT)};
        functions::OpenSingle operation{path};
        if (operation.run(*newLog))
        {
            int newLogId{newLog->getId()};
            openedLogs.append(std::move(newLog));
            logTabs.addTab(openedLogs.get(newLogId));
        }
    }
} catch(const std::exception& e)
{
    std::cout << "Open single file failed: " << e.what() << std::endl;
}

void TabController::removeLog(int id) const
{
    int parentId = openedLogs.get(id).getParentId();
    if (parentId != NO_PARENT) try
    {
        openedLogs.get(parentId).removeChild(id);
    } catch (std::exception&) {}
    openedLogs.remove(id);
}
} // namespace controllers
