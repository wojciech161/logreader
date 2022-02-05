#include "FunctionsController.hpp"
#include <exception>
#include <iostream>
#include "MainWindow.hpp"
#include "LogContainer.hpp"
#include "GetSelection.hpp"
#include "GrepDialog.hpp"
#include "Grep.hpp"
#include "NameCreator.hpp"
#include "FindDialog.hpp"
#include "Find.hpp"
#include "MarkDialog.hpp"
#include "Mark.hpp"

namespace controllers
{
FunctionsController::FunctionsController(view::MainWindow& appWindow)
: appWindow{appWindow}
, fileView{appWindow.getFileView()}
{
    std::cout << "FunctionsController is constructed\n";
}

FunctionsController::~FunctionsController()
{
    std::cout << "FunctionsController is destructed\n";
}

void FunctionsController::performGrep() const try
{
    view::LogContainer& currentTab{fileView.getCurrentTab()};
    view::GrepDialog dialog(appWindow, getSelection());
    auto result = dialog.show();
    if (result.success)
    {
        functions::Grep operation{currentTab.getLog(), result.query, result.regexp, result.caseSensitive, result.inverted};
        auto& newTab = currentTab.addTab(functions::createName(result.query, result.regexp, result.caseSensitive, result.inverted), true);
        operation.run(newTab);
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
}

void FunctionsController::performMark() const try
{
    const auto selectedText = getSelection(false);
    if (selectedText.empty())
    {
        view::MarkDialog dialog(appWindow);
        auto result = dialog.show();
        if (result.success)
        {
            functions::Mark operation{result.query};
            operation.run(fileView.getCurrentTab().getLog());
        }
    }
    else
    {
        functions::Mark operation{selectedText};
        operation.run(fileView.getCurrentTab().getLog());
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform mark: " << e.what() << std::endl;
}

void FunctionsController::performFind() const try
{
    view::FindDialog dialog(appWindow, getSelection());
    auto result = dialog.show();
    if (result.success)
    {
        functions::Find operation{result.query, result.caseSensitive};
        operation.run(fileView.getCurrentTab().getLog());
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform find: " << e.what() << std::endl;
}

std::string FunctionsController::getSelection(bool shouldUnmark) const try
{
    std::string result;
    functions::GetSelection operation{result, shouldUnmark};
    operation.run(fileView.getCurrentTab().getLog());
    return result;
}
catch(const std::exception& e)
{
    return "";
}

} // namespace controllers
