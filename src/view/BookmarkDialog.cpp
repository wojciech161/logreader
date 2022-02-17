#include "BookmarkDialog.hpp"
#include "MainWindow.hpp"
#include <iostream> // temporary

namespace view
{
BookmarkDialog::BookmarkDialog(MainWindow& parent)
: Gtk::Dialog{"Please type a bookmark name", parent}
{
    set_size_request(400, 100);
    get_vbox()->pack_start(textEdit, Gtk::PACK_SHRINK);
    add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    add_button("_Go!", Gtk::RESPONSE_OK);
    textEdit.set_activates_default(true);
    auto okButton = get_widget_for_response(Gtk::RESPONSE_OK);
    okButton->set_can_default(true);
    okButton->grab_default();
    show_all_children();
}

BookmarkDialog::Result BookmarkDialog::show()
{
    int result = run();
    switch(result)
    {
        case(Gtk::RESPONSE_OK):
        {
            return {true, textEdit.get_text()};
        }
        case(Gtk::RESPONSE_CANCEL):
        default:
        {
            return {};
        }
    }
}
} // namespace view
