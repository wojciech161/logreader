#include "BookmarkView.hpp"
#include "BaseTab.hpp"
#include <iostream>

namespace view
{
BookmarkView::BookmarkView()
: Gtk::Box{Gtk::ORIENTATION_VERTICAL}
, boxTitle{"Bookmarks:"}
, closeBookmarkButton{"Delete bookmark"}
{
    pack_start(boxTitle, Gtk::PACK_SHRINK);
    pack_start(bookmarkWindow, Gtk::PACK_EXPAND_WIDGET);
    pack_end(closeBookmarkButton, Gtk::PACK_SHRINK);

    bookmarkWindow.add(treeView);
    bookmarkWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    treeView.append_column("Line", columns.lineNumber);
    treeView.append_column("Name", columns.bookmarkName);
    treeView.signal_row_activated().connect(sigc::mem_fun(*this, &BookmarkView::onColumnActivated));
    treeView.columns_autosize();

    closeBookmarkButton.signal_clicked().connect(sigc::mem_fun(*this, &BookmarkView::onBookmarkClose));
}

const model::BookmarkColumns& BookmarkView::getColumns() const
{
    return columns;
}

void BookmarkView::update(BaseTab* baseTab, const Glib::RefPtr<Gtk::ListStore>& model)
{
    currentTab = baseTab;
    treeView.set_model(model);
}

void BookmarkView::onColumnActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*)
{
    if (currentTab)
    {
        currentTab->onBookmarkActivated(path);
    }
}

void BookmarkView::release(BaseTab* tab)
{
    if (currentTab == tab)
    {
        treeView.unset_model();
        currentTab = nullptr;
    }
}

void BookmarkView::onBookmarkClose()
{
    if (currentTab)
    {
        const auto selectionIter = treeView.get_selection()->get_selected();
        currentTab->deleteBookmark(selectionIter);
    }

}
} // namespaceview 
