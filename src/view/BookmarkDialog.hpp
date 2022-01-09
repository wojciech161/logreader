#pragma once

#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>

#include "MainWindow.hpp"

namespace view
{
class BookmarkDialog : public Gtk::Dialog
{
public:
    struct Result
    {
        bool success{false};
        std::string name{};
    };
    BookmarkDialog(MainWindow&);
    virtual ~BookmarkDialog() = default;

    Result show();
private:
    Gtk::Entry textEdit;
};
} // namespace view
