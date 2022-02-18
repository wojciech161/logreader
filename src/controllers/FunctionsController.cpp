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
#include "BookmarkView.hpp"
#include "LogList.hpp"
#include "Log.hpp"

namespace controllers
{
FunctionsController::FunctionsController(
    view::MainWindow& appWindow, model::LogList& openedLogs)
: appWindow{appWindow}
, fileView{appWindow.getFileView()}
, openedLogs{openedLogs}
, columns{appWindow.getBookmarkView().getColumns()}
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
    model::Log& currentLog = getCurrentLog();
    view::GrepDialog dialog(appWindow, getSelection());
    auto result = dialog.show();
    if (result.success)
    {
        functions::Grep operation{currentLog, result.query, result.regexp, result.caseSensitive, result.inverted};
        auto newLog{std::make_unique<model::Log>(functions::createName(
            result.query, result.regexp, result.caseSensitive, result.inverted), columns, currentLog.getId())};
        if (isGrepPresent(currentLog, newLog->getName()))
        {
            std::cout << "Grep is already present\n";
            return;
        }
        if (operation.run(*newLog))
        {
            int newLogId{newLog->getId()};
            openedLogs.append(std::move(newLog));
            currentTab.addTab(openedLogs.get(newLogId));
            currentLog.addChild(newLogId);
        }
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform grep: " << e.what() << std::endl;
}

void FunctionsController::performMark() const try
{
    view::LogContainer& currentTab{fileView.getCurrentTab()};
    model::Log& currentLog = getCurrentLog();
    const auto selectedText = getSelection(false);
    if (selectedText.empty())
    {
        view::MarkDialog dialog(appWindow);
        auto result = dialog.show();
        if (result.success)
        {
            functions::Mark operation{result.query};
            operation.run(currentLog);
        }
    }
    else
    {
        functions::Mark operation{selectedText};
        operation.run(currentLog);
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform mark: " << e.what() << std::endl;
}

void FunctionsController::performFind() const try
{
    model::Log& currentLog = getCurrentLog();
    view::LogView& currentLogView = fileView.getCurrentTab().getLog();
    view::FindDialog dialog(appWindow, getSelection());
    auto result = dialog.show();
    if (result.success)
    {
        Gtk::TextIter iterAtFound;
        functions::Find operation{result.query, result.caseSensitive, iterAtFound};
        if (operation.run(currentLog))
        {
            currentLogView.scrollTo(iterAtFound);
        }
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform find: " << e.what() << std::endl;
}

std::string FunctionsController::getSelection(bool shouldUnmark) const try
{
    std::string result;
    model::Log& currentLog = getCurrentLog();
    functions::GetSelection operation{result, shouldUnmark};
    operation.run(currentLog);
    return result;
}
catch(const std::exception& e)
{
    return "";
}

model::Log& FunctionsController::getCurrentLog() const
{
    int currentLogId = fileView.getCurrentTab().getLog().getModelId();
    if (currentLogId == -1)
    {
        throw std::runtime_error("Can't get current log!");
    }
    return openedLogs.get(currentLogId);
}

bool FunctionsController::isGrepPresent(const model::Log& parentLog, const std::string& grepName) const
{
    const auto& currentGreps{parentLog.getChildren()};
    return std::find_if(currentGreps.begin(), currentGreps.end(), [this, grepName](int logId) {
        try
        {
            return openedLogs.get(logId).getName() == grepName;
        }
        catch(const std::exception&)
        {
            return false;
        }
        
    }) != currentGreps.end();
}
} // namespace controllers
