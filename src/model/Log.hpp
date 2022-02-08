#pragma once

#include <string>
#include <gtksourceviewmm/buffer.h>
#include "BookmarkList.hpp"

namespace model
{
class Log
{
public:
    Log(int, const std::string&, const Bookmark&);
    ~Log();
    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;

    int getId() const;
    const std::string& getName() const;
    Glib::RefPtr<Gsv::Buffer>& getBuffer();
    const Glib::RefPtr<Gsv::Buffer> getBuffer() const;
    model::BookmarkList& getBookmarks();
    int getCurrentLine() const;

private:
    int id;
    std::string name;
    Glib::RefPtr<Gsv::Buffer> buffer;
    BookmarkList bookmarks;
};
} // namespace model
