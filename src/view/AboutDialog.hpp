#pragma once

#include <gtkmm/aboutdialog.h>

namespace view
{
class MainWindow;
} // namespace view

namespace view
{
class AboutDialog : public Gtk::AboutDialog
{
public:
    AboutDialog(MainWindow&);
    virtual ~AboutDialog() = default;
};
} // namespace view
