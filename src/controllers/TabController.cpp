#include "TabController.hpp"
#include <exception>
#include <iostream>
#include "LogContainer.hpp"
#include "MainWindow.hpp"
#include "FileChooser.hpp"
#include "OpenSingle.hpp"
#include "NameCreator.hpp"

namespace controllers
{
TabController::TabController(view::MainWindow& appWindow)
: appWindow{appWindow}
, logTabs{appWindow.getFileView()}
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
        functions::OpenSingle operation{path};
        auto& newTab = logTabs.addTab(functions::createName(path), true);
        operation.run(newTab);
    }
} catch(const std::exception& e)
{
    std::cout << "Open single file failed: " << e.what() << std::endl;
}
} // namespace controllers
