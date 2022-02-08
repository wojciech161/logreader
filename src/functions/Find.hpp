#pragma once

#include <gtkmm/textiter.h>
#include <string>
#include "Operation.hpp"

namespace functions
{
class Find : public Operation
{
public:
    Find(const std::string&, bool, Gtk::TextIter&);
    ~Find() = default;

    bool run(view::LogView&) const override;
    bool run(model::Log&) const override;

private:
    std::string query;
    bool caseSensitive;
    Gtk::TextIter& iterAtFound;
};
} // namespace functions
