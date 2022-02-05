#pragma once

#include <giomm/simpleactiongroup.h>
#include <gtkmm/application.h>
#include "MainWindow.hpp"
#include "FunctionsController.hpp"
#include "TabController.hpp"
#include "BookmarkController.hpp"

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
    view::MainWindow appWindow;
    TabController tabController;
    FunctionsController functionsController;
    BookmarkController bookmarkController;
};
} // namespace controllers
