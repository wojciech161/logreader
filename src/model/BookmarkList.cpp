#include "BookmarkList.hpp"
#include "Bookmark.hpp"

namespace model
{
BookmarkList::BookmarkList(const Bookmark& columns)
: columns{columns}
, bookmarks{Gtk::ListStore::create(columns)}
{
    bookmarks->set_sort_column(0, Gtk::SORT_ASCENDING);
}

BookmarkList::~BookmarkList()
{
    bookmarks->clear();
}

void BookmarkList::add(int lineNumber, const std::string& name)
{
    Gtk::TreeModel::Row row = *(bookmarks->append());
    row[columns.lineNumber] = lineNumber + 1;
    row[columns.bookmarkName] = name;
}

void BookmarkList::remove(const Gtk::TreeModel::iterator& iter)
{
    if (iter)
    {
        bookmarks->erase(iter);
    }
}

int BookmarkList::getBookmarkLine(const Gtk::TreeModel::Path& path)
{
    auto childIter = bookmarks->get_iter(path);
    if (childIter)
    {
        Gtk::TreeModel::Row row = *childIter;
        return row[columns.lineNumber] - 1;
    }
    return -1;
}

const Glib::RefPtr<Gtk::ListStore>& BookmarkList::getModel() const
{
    return bookmarks;
}
} // namespace model
