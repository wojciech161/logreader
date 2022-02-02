#pragma once

#include <gtksourceviewmm/buffer.h>
#include "BookmarkList.hpp"

namespace model
{
class Log
{
public:
    Log(int);
    ~Log();
    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;

    int getId() const;
    Glib::RefPtr<Gsv::Buffer>& getBuffer();
    const Glib::RefPtr<Gsv::Buffer> getBuffer() const;
    int getCurrentLine() const;

private:
    int id;
    Glib::RefPtr<Gsv::Buffer> buffer;
};
} // namespace model
