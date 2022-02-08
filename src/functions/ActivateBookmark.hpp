#pragma once

#include <string>
#include <gtkmm/textiter.h>
#include "Operation.hpp"

namespace functions
{
class ActivateBookmark : public Operation
{
public:
    ActivateBookmark(int, Gtk::TextIter&);
    virtual ~ActivateBookmark() = default;

    bool run(view::LogView&) const override;
    bool run(model::Log&) const override;

private:
    int lineNumber;
    Gtk::TextIter& iterAtLine;
};
} // namespace functions
