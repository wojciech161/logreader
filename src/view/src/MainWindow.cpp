#include "MainWindow.hpp"

namespace view
{
MainWindow::MainWindow()
{
    set_resizable();
    set_title("Log Reader v0.1");
    set_default_size(500, 500);
    add(mainContainer);
    show_all_children();
}
} // namespace view
