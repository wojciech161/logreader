#pragma once

#include <gtkmm/box.h>

namespace view
{
class MainContainer : public Gtk::Box
{
public:
    MainContainer();
    virtual ~MainContainer() = default;
};
} // namespace view