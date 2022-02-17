#include "LogView.hpp"
#include "Log.hpp"
#include "TabController.hpp"

#include <iostream> // temporary

namespace view
{
LogView::LogView(const controllers::TabController& tabController)
: modelId{-1}
, tabController{tabController}
{
    std::cout << "LogView is constructed, id: " << modelId << "\n";
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
}

LogView::LogView(const model::Log& log, const controllers::TabController& tabController)
: modelId{log.getId()}
, tabController{tabController}
{
    std::cout << "LogView is constructed\n";
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    add(textView);
    textView.set_editable(false);
    textView.set_cursor_visible(true);
    textView.set_show_line_numbers(true);
    textView.set_highlight_current_line(true);
    textView.set_source_buffer(log.getBuffer());
    textView.show();
}

LogView::~LogView()
{
    std::cout << "LogView is destructed\n";
    if (modelId != -1) tabController.removeLog(modelId);
}

void LogView::scrollTo(Gtk::TextIter& iter)
{
    textView.scroll_to(iter);
}

int LogView::getModelId() const
{
    return modelId;
}
} // namespace view
