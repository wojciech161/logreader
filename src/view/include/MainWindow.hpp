#pragma once

#include <gtkmm/window.h>
#include "MainContainer.hpp"

namespace view
{
class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    ~MainWindow() override = default;

private:
    MainContainer mainContainer;
};
} // namespace view
