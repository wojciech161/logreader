#include "MainWindow.hpp"
#include <gtkmm/menubar.h>
#include "FileChooser.hpp"
#include "AboutDialog.hpp"
#include "BookmarkDialog.hpp"
#include "FindDialog.hpp"
#include "MarkDialog.hpp"
#include "GrepDialog.hpp"
#include "Find.hpp"
#include "Grep.hpp"
#include "Mark.hpp"
#include "AddBookmark.hpp"
#include "GetSelection.hpp"
#include "OpenSingle.hpp"
#include "NameCreator.hpp"
#include <iostream>

namespace
{
std::string getSelection(view::LogView& logView, bool shouldUnmark = true) try
{
    std::string result;
    functions::GetSelection operation{result, shouldUnmark};
    operation.run(logView);
    return result;
}
catch(const std::exception& e)
{
    std::cerr << "Unable to get selected text: " << e.what() << '\n';
    return "";
}
} // namespace

namespace view
{
MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application>& app)
: topContainer(Gtk::ORIENTATION_VERTICAL)
, mainContainer(Gtk::ORIENTATION_HORIZONTAL)
, bookmarkView{}
, fileView{bookmarkView, false}
{
    set_title("LogReader version: 0.03");
    set_default_size(600, 600);
    signal_size_allocate().connect(sigc::mem_fun(*this, &MainWindow::onResize));
    initActions();
    buildGui();
    setupKeyboardShortcuts(app);
    show_all_children();
}

void MainWindow::onActionFileOpen() try
{
    FileChooser fileChooser(*this);
    std::string path = fileChooser.getFilepath();
    if (not path.empty())
    {
        functions::OpenSingle operation{path};
        auto& newTab = fileView.addTab(functions::createName(path), true);
        operation.run(newTab);
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform find: " << e.what() << std::endl;
}

void MainWindow::onActionToolsGrep() try
{
    LogContainer& currentTab{fileView.getCurrentTab()};
    GrepDialog dialog(*this, getSelection(currentTab.getLog()));
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

void MainWindow::onActionToolsFind() try
{
    LogView& currentLog{fileView.getCurrentTab().getLog()};
    FindDialog dialog(*this, getSelection(currentLog));
    auto result = dialog.show();
    if (result.success)
    {
        functions::Find operation{result.query, result.caseSensitive};
        operation.run(currentLog);
    }
} catch(const std::exception& e)
{
    std::cout << "Unable to perform find: " << e.what() << std::endl;
}

void MainWindow::onActionToolsMark() try
{
    LogView& currentLog{fileView.getCurrentTab().getLog()};
    const auto selectedText = getSelection(currentLog, false);
    if (selectedText.empty())
    {
        MarkDialog dialog(*this);
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

void MainWindow::onActionToolsBookmark() try
{
    BookmarkDialog dialog(*this);
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

void MainWindow::onActionHelpAbout()
{
    AboutDialog dialog(*this);
    dialog.run();
}

void MainWindow::onResize(Gtk::Allocation& allocation)
{
    constexpr int maxWidth = 300;
    int bookmarkListWidth = get_width() * 0.2;
    bookmarkListWidth > maxWidth ?
        bookmarkView.set_size_request(maxWidth) :
        bookmarkView.set_size_request(bookmarkListWidth);
}

void MainWindow::initActions()
{
    refActionGroup = Gio::SimpleActionGroup::create();
    refActionGroup->add_action("open", sigc::mem_fun(*this, &MainWindow::onActionFileOpen));
    refActionGroup->add_action("quit", sigc::mem_fun(*this, &MainWindow::hide));
    refActionGroup->add_action("grep", sigc::mem_fun(*this, &MainWindow::onActionToolsGrep));
    refActionGroup->add_action("find", sigc::mem_fun(*this, &MainWindow::onActionToolsFind));
    refActionGroup->add_action("mark", sigc::mem_fun(*this, &MainWindow::onActionToolsMark));
    refActionGroup->add_action("bookmark", sigc::mem_fun(*this, &MainWindow::onActionToolsBookmark));
    refActionGroup->add_action("about", sigc::mem_fun(*this, &MainWindow::onActionHelpAbout));
    insert_action_group("actions", refActionGroup);
}

void MainWindow::buildGui()
{
    auto menuBar = menuBuilder.build();
    mainContainer.pack_start(bookmarkView, Gtk::PACK_SHRINK, 10);
    mainContainer.pack_start(fileView, Gtk::PACK_EXPAND_WIDGET);
    add(topContainer);
    topContainer.pack_start(*menuBar, Gtk::PACK_SHRINK);
    topContainer.pack_end(mainContainer);
}

void MainWindow::setupKeyboardShortcuts(const Glib::RefPtr<Gtk::Application>& app)
{
    app->set_accel_for_action("actions.open", "<Primary>o");
    app->set_accel_for_action("actions.quit", "<Primary>q");
    app->set_accel_for_action("actions.grep", "<Primary>g");
    app->set_accel_for_action("actions.find", "<Primary>f");
    app->set_accel_for_action("actions.mark", "<Primary>m");
    app->set_accel_for_action("actions.bookmark", "<Primary>b");
}
} // namespace view
