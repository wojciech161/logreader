#include "FindDialog.hpp"

namespace view
{
FindDialog::FindDialog(MainWindow& parent, const std::string& text)
: Gtk::Dialog{"Please type a search query", parent}
, caseInsensitiveCheck{"Case sensitive"}
{
    set_size_request(400, 100);
    searchEntry.set_text(text);
    get_vbox()->pack_start(searchEntry, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(caseInsensitiveCheck, Gtk::PACK_SHRINK);
    add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    add_button("_Find Next!", Gtk::RESPONSE_OK);
    searchEntry.set_activates_default(true);
    auto okButton = get_widget_for_response(Gtk::RESPONSE_OK);
    okButton->set_can_default(true);
    okButton->grab_default();
    show_all_children();
}

FindDialog::Result FindDialog::show()
{
    int result = run();
    if (Gtk::RESPONSE_OK == result)
    {
        return FindDialog::Result{true, searchEntry.get_text(), caseInsensitiveCheck.get_active()};
    }
    return FindDialog::Result{};
}
} // namespace view
