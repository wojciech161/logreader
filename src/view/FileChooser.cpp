#include "FileChooser.hpp"
#include "MainWindow.hpp"

namespace view
{
FileChooser::FileChooser(MainWindow& parent)
: Gtk::FileChooserDialog{"Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN}
{
    set_transient_for(parent);
    add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    add_button("_Open", Gtk::RESPONSE_OK);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    add_filter(filter_any);
}

std::string FileChooser::getFilepath()
{
    int result = run();
    switch(result)
    {
        case(Gtk::RESPONSE_OK):
        {
            return get_filename();
            break;
        }
        case(Gtk::RESPONSE_CANCEL):
        default:
        {
            break;
        }
    }
    return std::string();
}
} // namespace view
