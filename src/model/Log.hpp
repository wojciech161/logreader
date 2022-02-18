#pragma once

#include <string>
#include <vector>
#include <gtksourceviewmm/buffer.h>
#include "BookmarkList.hpp"

namespace model
{
class Log
{
public:
    Log(const std::string&, const Bookmark&, int);
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
    const model::BookmarkList& getBookmarks() const;
    void addChild(int);
    void removeChild(int);
    int getParentId() const;
    const std::vector<int>& getChildren() const;

private:
    int id;
    std::string name;
    const int parentId;
    std::vector<int> children;
    Glib::RefPtr<Gsv::Buffer> buffer;
    BookmarkList bookmarks;
};
} // namespace model
