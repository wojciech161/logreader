#include "GrepDialog.hpp"
#include "MainWindow.hpp"
#include <iostream> // temporary

namespace view
{
GrepDialog::GrepDialog(MainWindow& parent, const std::string& text)
: Gtk::Dialog{"Please type a grep", parent}
, checkBox{Gtk::ORIENTATION_HORIZONTAL}
, regexpCheck{"Regular expression"}
, caseSensitiveCheck{"Case sensitive"}
, invertedCheck{"Inverted"}
{
    set_size_request(400, 100);
    textEdit.set_text(text);
    checkBox.pack_start(regexpCheck);
    checkBox.pack_start(caseSensitiveCheck);
    checkBox.pack_start(invertedCheck);
    get_vbox()->pack_start(textEdit, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(checkBox);
    add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    add_button("_Go!", Gtk::RESPONSE_OK);
    textEdit.set_activates_default(true);
    auto okButton = get_widget_for_response(Gtk::RESPONSE_OK);
    okButton->set_can_default(true);
    okButton->grab_default();
    show_all_children();
}

GrepDialog::Result GrepDialog::show()
{
    int result = run();
    switch(result)
    {
        case(Gtk::RESPONSE_OK):
        {
            return {
                true,
                textEdit.get_text(),
                regexpCheck.get_active(),
                caseSensitiveCheck.get_active(),
                invertedCheck.get_active()
            };
        }
        case(Gtk::RESPONSE_CANCEL):
        default:
        {
            return {};
        }
    }
}
} // namespace view
