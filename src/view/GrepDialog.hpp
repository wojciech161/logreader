#pragma once

#include <string>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>

#include "MainWindow.hpp"

namespace view
{
class GrepDialog : public Gtk::Dialog
{
public:
    struct Result
    {
        bool success{false};
        std::string query{};
        bool regexp{false};
        bool caseSensitive{false};
        bool inverted{false};
    };
    GrepDialog(MainWindow&, const std::string&);
    virtual ~GrepDialog() = default;

    Result show();
private:
    Gtk::Entry textEdit;
    Gtk::Box checkBox;
    Gtk::CheckButton regexpCheck;
    Gtk::CheckButton caseSensitiveCheck;
    Gtk::CheckButton invertedCheck;
};
} // namespace view
