#pragma once
#include "view/Application.hpp"
#include <gtkmm/application.h>
#include "MainWindow.hpp"

namespace view
{
class ApplicationImpl : public Application
{
public:
    ApplicationImpl(int, char**);
    ~ApplicationImpl() override = default;
    int run() override;

public:
    Glib::RefPtr<Gtk::Application> app;
    MainWindow window;
};
} // namespace view
