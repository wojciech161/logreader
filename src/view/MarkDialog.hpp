#pragma once

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/searchentry.h>

namespace view
{
class MainWindow;
} // namespace view


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
