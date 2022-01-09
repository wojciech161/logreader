#include "AboutDialog.hpp"
#include "MainWindow.hpp"

namespace view
{
AboutDialog::AboutDialog(MainWindow& mainWindow)
{
    set_transient_for(mainWindow);

    // set_logo(Gdk::Pixbuf::create_from_resource("/about/gtkmm_logo.gif", -1, 40, true));
    set_program_name("LogViewer");
    set_version("0.1");
    set_copyright("wojciech161@gmail.com");
    set_comments("App helpful in log analysis");
    set_license("LGPL");
    show_all_children();
}
} // namespace view
