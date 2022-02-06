#include "TabLabel.hpp"

namespace view
{
TabLabel::TabLabel(const std::string& name, const std::function<void()>& closeFunction)
: Gtk::Box{Gtk::ORIENTATION_HORIZONTAL}
, nameLabel{name}
, closeButton{"X"}
{
    closeConnection = closeButton.signal_clicked().connect(closeFunction);
    pack_start(nameLabel, Gtk::PACK_SHRINK, 5);
    pack_start(closeButton, Gtk::PACK_SHRINK);
    show_all_children();
}

TabLabel::~TabLabel()
{
    closeConnection.disconnect();
}
} // namespace view
