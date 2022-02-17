#pragma once

#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>

namespace view
{
class MainWindow;
} // namespace view

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
