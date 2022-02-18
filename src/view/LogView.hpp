#pragma once

#include <gtkmm/scrolledwindow.h>
#include <gtksourceviewmm/view.h>

namespace controllers
{
class TabController;
} // namespace controllers
namespace model
{
class Log;
} // namespace model

namespace view
{
class LogView : public Gtk::ScrolledWindow
{
public:
    LogView(controllers::TabController&);
    LogView(const model::Log&, controllers::TabController&);
    virtual ~LogView();

    void scrollTo(Gtk::TextIter&);
    int getModelId() const;

private:
    Gsv::View textView;
    int modelId;
    controllers::TabController& tabController;
};
} // namespace view
