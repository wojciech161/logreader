#pragma once

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/searchentry.h>
#include "MainWindow.hpp"

namespace view
{
class MarkDialog : public Gtk::Dialog
{
public:
    struct Result
    {
        bool success{false};
        std::string query{};
    };

    MarkDialog(MainWindow&);
    virtual ~MarkDialog() = default;

    Result show();

private:
    Gtk::Label infoLabel;
    Gtk::SearchEntry searchEntry;
};
} // namespace view
