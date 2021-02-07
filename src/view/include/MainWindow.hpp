#pragma once

#include <gtkmm/window.h>

namespace view
{
class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    ~MainWindow() override = default;
};
} // namespace view
