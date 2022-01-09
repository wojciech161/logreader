#pragma once

#include <gtksourceviewmm/buffer.h>
#include <functional>
#include <string>

namespace functions
{
class LogInserter
{
public:
    LogInserter(Glib::RefPtr<Gsv::Buffer>&);
    ~LogInserter() = default;

    void addLine(const std::string&);
private:
    Glib::RefPtr<Gsv::Buffer>& buffer;
    Glib::RefPtr<Gtk::TextTag> errorTag;
    Glib::RefPtr<Gtk::TextTag> warningTag;
    std::function<bool(const std::string&)> isError;
    std::function<bool(const std::string&)> isWarning;
};
} // namespace functions
