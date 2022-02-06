#pragma once

#include <functional>
#include <string>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

namespace view
{
class TabLabel : public Gtk::Box
{
public:
    TabLabel(const std::string&, const std::function<void()>&);
    virtual ~TabLabel();

private:
    Gtk::Label nameLabel;
    Gtk::Button closeButton;
    sigc::connection closeConnection;
};
} // namespace view
