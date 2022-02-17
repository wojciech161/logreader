#include "BookmarkView.hpp"
#include "BookmarkController.hpp"
#include <iostream>

namespace view
{
BookmarkView::BookmarkView(const controllers::BookmarkController& controller)
: Gtk::Box{Gtk::ORIENTATION_VERTICAL}
, boxTitle{"Bookmarks:"}
, closeBookmarkButton{"Delete bookmark"}
{
    std::cout << "BookmarkView is constructed\n";
    pack_start(boxTitle, Gtk::PACK_SHRINK);
    pack_start(bookmarkWindow, Gtk::PACK_EXPAND_WIDGET);
    pack_end(closeBookmarkButton, Gtk::PACK_SHRINK);

    bookmarkWindow.add(treeView);
    bookmarkWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    treeView.append_column("Line", columns.lineNumber);
    treeView.append_column("Name", columns.bookmarkName);
    treeView.columns_autosize();

    connections.emplace_back(treeView.signal_row_activated().connect(
        sigc::mem_fun(controller, &controllers::BookmarkController::activateBookmark)));
    connections.emplace_back(closeBookmarkButton.signal_clicked().connect(
        sigc::mem_fun(controller, &controllers::BookmarkController::closeBookmark)));
}

BookmarkView::~BookmarkView()
{
    std::cout << "BookmarkView is destructed\n";
    for (auto& connection : connections)
    {
        connection.disconnect();
    }
    connections.clear();
}

const model::Bookmark& BookmarkView::getColumns() const
{
    return columns;
}

void BookmarkView::update(const Glib::RefPtr<Gtk::ListStore>& model)
{
    treeView.set_model(model);
}

Gtk::TreeModel::iterator BookmarkView::getCurrentSelection()
{
    return treeView.get_selection()->get_selected();
}
} // namespaceview 
