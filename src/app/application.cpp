#include <gtkmm/application.h>
#include "MainWindow.hpp"

namespace
{
const char* APP_NAME{"pl.logreader"};
} // namespace

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, APP_NAME);
    view::MainWindow mainWindow{app};
    return app->run(mainWindow);
}
