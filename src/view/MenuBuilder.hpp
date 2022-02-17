#pragma once

#include <gtkmm/builder.h>
#include <gtkmm/menubar.h>
#include <giomm/simpleactiongroup.h>

namespace view
{
class MenuBuilder
{
public:
    MenuBuilder() = default;
    ~MenuBuilder() = default;

    Gtk::MenuBar* build();

private:
    Glib::RefPtr<Gtk::Builder> refBuilder;
};
} // namespace view
