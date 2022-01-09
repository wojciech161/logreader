#pragma once

#include <string>
#include <gtkmm/checkbutton.h>
#include <gtkmm/dialog.h>
#include <gtkmm/searchentry.h>
#include "MainWindow.hpp"

namespace view
{
class FindDialog : public Gtk::Dialog
{
public:
    struct Result
    {
        bool success{false};
        std::string query{};
        bool caseSensitive{false};
    };

    FindDialog(MainWindow&, const std::string&);
    virtual ~FindDialog() = default;

    Result show();

private:
    Gtk::SearchEntry searchEntry;
    Gtk::CheckButton caseInsensitiveCheck;
};
} // namespace view
