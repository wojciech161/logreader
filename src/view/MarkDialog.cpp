#include "MarkDialog.hpp"
#include "MainWindow.hpp"

namespace view
{
MarkDialog::MarkDialog(MainWindow& parent)
: Gtk::Dialog{"Please type a word to mark/unmark", parent}
, infoLabel{"Case insensitive. To unmark, type the word again"}
{
    set_size_request(400, 100);
    get_vbox()->pack_start(infoLabel, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(searchEntry, Gtk::PACK_SHRINK);
    add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    add_button("_Mark!", Gtk::RESPONSE_OK);
    searchEntry.set_activates_default(true);
    auto okButton = get_widget_for_response(Gtk::RESPONSE_OK);
    okButton->set_can_default(true);
    okButton->grab_default();
    show_all_children();
}

MarkDialog::Result MarkDialog::show()
{
    int result = run();
    if (Gtk::RESPONSE_OK == result)
    {
        return MarkDialog::Result{true, searchEntry.get_text()};
    }
    return MarkDialog::Result{};
}
} // namespace view
