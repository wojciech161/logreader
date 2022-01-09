#pragma once

#include <gtkmm/application.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <giomm/simpleactiongroup.h>

#include "BookmarkView.hpp"
#include "MenuBuilder.hpp"
#include "FileView.hpp"

namespace view
{
class MainWindow : public Gtk::Window
{
public:
    MainWindow(const Glib::RefPtr<Gtk::Application>&);
    virtual ~MainWindow() = default;

private: /*actions*/
    void onActionFileOpen();
    void onActionFileQuit();
    void onActionToolsGrep();
    void onActionToolsFind();
    void onActionToolsMark();
    void onActionToolsBookmark();
    void onActionHelpAbout();
    void onResize(Gtk::Allocation& allocation);

private: /*functions*/
    void initActions();
    void buildGui();
    void setupKeyboardShortcuts(const Glib::RefPtr<Gtk::Application>& app);

private: /*members*/
    // GUI Elements
    Gtk::Box topContainer;
    Gtk::Box mainContainer;
    BookmarkView bookmarkView;
    FileView fileView;

    // Helpers
    MenuBuilder menuBuilder;
    Glib::RefPtr<Gio::SimpleActionGroup> refActionGroup;
};
} // namespace view
