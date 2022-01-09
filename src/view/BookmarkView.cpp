#include "BookmarkView.hpp"
#include "BaseTab.hpp"
#include <iostream>

namespace view
{
BookmarkView::BookmarkView()
{
    add(treeView);
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    refTreeModel = Gtk::ListStore::create(columns);
    treeView.set_model(refTreeModel);
    treeView.append_column("Line", columns.lineNumber);
    treeView.append_column("Name", columns.bookmarkName);
    treeView.signal_row_activated().connect(sigc::mem_fun(*this, &BookmarkView::onColumnActivated));
}

void BookmarkView::update(BaseTab* baseTab, const model::BookmarkList& bookmarks)
{
    currentTab = baseTab;
    refTreeModel->clear();
    for(const auto& bookmark : bookmarks)
    {
        Gtk::TreeModel::Row row = *(refTreeModel->append());
        row[columns.lineNumber] = bookmark.lineNumber + 1;
        row[columns.bookmarkName] = bookmark.name;
    }
}

void BookmarkView::onColumnActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*)
{
    auto childIter = refTreeModel->get_iter(path);
    if (childIter and currentTab)
    {
        Gtk::TreeModel::Row row = *childIter;
        currentTab->goToLine(row[columns.lineNumber] - 1);
    }
}

void BookmarkView::release(BaseTab* tab)
{
    if (currentTab == tab)
    {
        currentTab = nullptr;
        clear();
    }
}

void BookmarkView::clear()
{
    refTreeModel->clear();
}
} // namespaceview 
