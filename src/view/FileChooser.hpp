#pragma once

#include <string>
#include <gtkmm/filechooserdialog.h>

namespace view
{
class MainWindow;
} // namespace view

namespace view
{
class FileChooser : public Gtk::FileChooserDialog
{
public:
    FileChooser(MainWindow&);
    virtual ~FileChooser() = default;

    std::string getFilepath();
};
} // namespace view
