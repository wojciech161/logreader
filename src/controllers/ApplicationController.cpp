#include "ApplicationController.hpp"
#include "AboutDialog.hpp"

namespace
{
const char* APP_NAME{"pl.logreader"};
} // namespace

namespace controllers
{
ApplicationController::ApplicationController(int argc, char** argv)
: application{Gtk::Application::create(argc, argv, APP_NAME)}
, refActionGroup{Gio::SimpleActionGroup::create()}
, tabController{appWindow}
, functionsController{appWindow}
, bookmarkController{appWindow}
, appWindow{bookmarkController, tabController}
{
    initActions();
    setupKeyboardShortcuts();
}

int ApplicationController::run()
{
    return application->run(appWindow);
}

void ApplicationController::initActions()
{
    refActionGroup = Gio::SimpleActionGroup::create();
    refActionGroup->add_action("open", sigc::mem_fun(&tabController, &TabController::openSingleFile));
    refActionGroup->add_action("quit", sigc::mem_fun(*this, &ApplicationController::closeApp));
    refActionGroup->add_action("grep", sigc::mem_fun(&functionsController, &FunctionsController::performGrep));
    refActionGroup->add_action("find", sigc::mem_fun(&functionsController, &FunctionsController::performFind));
    refActionGroup->add_action("mark", sigc::mem_fun(&functionsController, &FunctionsController::performMark));
    refActionGroup->add_action("bookmark", sigc::mem_fun(&bookmarkController, &BookmarkController::addBookmark));
    refActionGroup->add_action("about", sigc::mem_fun(*this, &ApplicationController::showAboutDialog));
    appWindow.insert_action_group("actions", refActionGroup);
}

void ApplicationController::setupKeyboardShortcuts()
{
    application->set_accel_for_action("actions.open", "<Primary>o");
    application->set_accel_for_action("actions.quit", "<Primary>q");
    application->set_accel_for_action("actions.grep", "<Primary>g");
    application->set_accel_for_action("actions.find", "<Primary>f");
    application->set_accel_for_action("actions.mark", "<Primary>m");
    application->set_accel_for_action("actions.bookmark", "<Primary>b");
}

void ApplicationController::closeApp()
{
    appWindow.hide();
}

void ApplicationController::showAboutDialog()
{
    view::AboutDialog dialog(appWindow);
    dialog.run();
}
} // namespace controllers
