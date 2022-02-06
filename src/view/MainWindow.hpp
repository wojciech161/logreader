#pragma once

#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

#include "BookmarkView.hpp"
#include "MenuBuilder.hpp"
#include "LogContainer.hpp"

namespace view
{
class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    virtual ~MainWindow();

    BookmarkView& getBookmarkView();
    LogContainer& getFileView();

private:
    void buildGui();
    void onResize(Gtk::Allocation& allocation);

private:
    Gtk::Box topContainer;
    Gtk::Box mainContainer;
    BookmarkView bookmarkView;
    LogContainer fileView;
    MenuBuilder menuBuilder;
    sigc::connection resizeConnection;
};
} // namespace view
