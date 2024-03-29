#include "MainWindow.hpp"
#include <iostream>
#include <gtkmm/menubar.h>

namespace view
{
MainWindow::MainWindow(
    const controllers::BookmarkController& bookmarkController,
    controllers::TabController& tabController)
: topContainer(Gtk::ORIENTATION_VERTICAL)
, mainContainer(Gtk::ORIENTATION_HORIZONTAL)
, bookmarkView{bookmarkController}
, fileView{bookmarkController, tabController}
{
    std::cout << "MainWindow is constructed\n";
    set_title("LogReader version: 0.04");
    set_default_size(600, 600);
    resizeConnection = signal_size_allocate().connect(
        sigc::mem_fun(*this, &MainWindow::onResize));
    buildGui();
    show_all_children();
}

MainWindow::~MainWindow()
{
    std::cout << "MainWindow is destructed\n";
    resizeConnection.disconnect();
}

BookmarkView& MainWindow::getBookmarkView()
{
    return bookmarkView;
}

LogContainer& MainWindow::getFileView()
{
    return fileView;
}

void MainWindow::onResize(Gtk::Allocation& allocation)
{
    constexpr int maxWidth = 300;
    int bookmarkListWidth = get_width() * 0.2;
    bookmarkListWidth > maxWidth ?
        bookmarkView.set_size_request(maxWidth) :
        bookmarkView.set_size_request(bookmarkListWidth);
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
} // namespace view
