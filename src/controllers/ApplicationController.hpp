#pragma once

#include <giomm/simpleactiongroup.h>
#include <gtkmm/application.h>
#include "MainWindow.hpp"
#include "FunctionsController.hpp"
#include "TabController.hpp"
#include "BookmarkController.hpp"
#include "LogList.hpp"

namespace controllers
{
class ApplicationController
{
public:
    ApplicationController(int, char**);
    ~ApplicationController() = default;

    int run();

private:
    void initActions();
    void setupKeyboardShortcuts();
    void closeApp();
    void showAboutDialog();

private:
    Glib::RefPtr<Gtk::Application> application;
    Glib::RefPtr<Gio::SimpleActionGroup> refActionGroup;
    TabController tabController;
    FunctionsController functionsController;
    BookmarkController bookmarkController;
    view::MainWindow appWindow;
    model::LogList openedLogs;
};
} // namespace controllers
