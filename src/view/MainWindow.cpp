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
#include <iostream>

namespace view
{
MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application>& app)
: topContainer(Gtk::ORIENTATION_VERTICAL)
, mainContainer(Gtk::ORIENTATION_HORIZONTAL)
, bookmarkView{}
, fileView{bookmarkView}
{
    set_title("LogReader version: 0.01");
    set_default_size(600, 600);
    signal_size_allocate().connect(sigc::mem_fun(*this, &MainWindow::onResize));
    initActions();
    buildGui();
    setupKeyboardShortcuts(app);
    show_all_children();
}

void MainWindow::onActionFileOpen()
{
    FileChooser fileChooser(*this);
    std::string path = fileChooser.getFilepath();
    if (not path.empty())
    {
        fileView.addFile(path);
    }
}

void MainWindow::onActionFileQuit()
{
    hide();
}

void MainWindow::onActionToolsGrep()
{
    GrepDialog dialog(*this, fileView.getSelectedText());
    auto result = dialog.show();
    if (result.success)
    {
        functions::Grep operation{result.query, result.regexp, result.caseSensitive, result.inverted};
        fileView.addGrep(operation);
    }
}

void MainWindow::onActionToolsFind()
{
    FindDialog dialog(*this, fileView.getSelectedText());
    auto result = dialog.show();
    if (result.success)
    {
        functions::Find operation{result.query, result.caseSensitive};
        fileView.findNext(operation);
    }
}

void MainWindow::onActionToolsMark()
{
    const auto selectedText = fileView.getSelectedText();
    if (selectedText.empty())
    {
        MarkDialog dialog(*this);
        auto result = dialog.show();
        if (result.success)
        {
            functions::Mark operation{result.query};
            fileView.markWords(operation);
        }
    }
    else
    {
        functions::Mark operation{selectedText};
        fileView.markWords(operation);
    }
}

void MainWindow::onActionToolsBookmark()
{
    BookmarkDialog dialog(*this);
    auto result = dialog.show();
    if (result.success)
    {
        fileView.addBookmark(result.name);
    }
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
        bookmarkView.set_min_content_width(maxWidth) :
        bookmarkView.set_min_content_width(bookmarkListWidth);
}

void MainWindow::initActions()
{
    refActionGroup = Gio::SimpleActionGroup::create();
    refActionGroup->add_action("open", sigc::mem_fun(*this, &MainWindow::onActionFileOpen));
    refActionGroup->add_action("quit", sigc::mem_fun(*this, &MainWindow::onActionFileQuit));
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