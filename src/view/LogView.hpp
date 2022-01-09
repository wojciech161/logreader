#pragma once

#include <string>

#include <gtkmm/scrolledwindow.h>
#include <gtksourceviewmm/buffer.h>
#include <gtksourceviewmm/view.h>
#include "BufferCreator.hpp"

namespace view
{
class LogView : public Gtk::ScrolledWindow
{
public:
    LogView(const functions::BufferCreator&);
    virtual ~LogView() = default;

    const Glib::RefPtr<Gsv::Buffer>& getBuffer() const;
    int getCurrentLine() const;
    void goToLine(int);
    std::string getSelectedText() const;

private:
    Gsv::View textView;
    Glib::RefPtr<Gsv::Buffer> buffer;
};
} // namespace view
