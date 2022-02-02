#include "BookmarkView.hpp"
#include "LogView.hpp"
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

const model::Bookmark& BookmarkView::getColumns() const
{
    return columns;
}

void BookmarkView::update(LogView* logView, const Glib::RefPtr<Gtk::ListStore>& model)
{
    currentLog = logView;
    treeView.set_model(model);
}

void BookmarkView::onColumnActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*)
{
    if (not currentLog) return;
    int bookmarkLine = currentLog->getBookmarks().getBookmarkLine(path);
    if (bookmarkLine > 0)
    {
        currentLog->goToLine(bookmarkLine);
    }
}

void BookmarkView::release(LogView* log)
{
    if (currentLog == log)
    {
        treeView.unset_model();
        currentLog = nullptr;
    }
}

void BookmarkView::onBookmarkClose()
{
    if (currentLog)
    {
        const auto selectionIter = treeView.get_selection()->get_selected();
        currentLog->getBookmarks().remove(selectionIter);
    }

}
} // namespaceview 
