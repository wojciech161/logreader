#include "GetSelection.hpp"
#include <gtksourceviewmm/buffer.h>
#include "LogView.hpp"

namespace functions
{
GetSelection::GetSelection(std::string& result, bool shouldUnselect)
: operationResult{result}
, shouldUnselect{shouldUnselect}
{
}

void GetSelection::run(view::LogView& logView) const
{
    const auto& buffer{logView.getBuffer()};
    Gtk::TextIter selectionStart, selectionEnd;
    if (buffer->get_selection_bounds(selectionStart, selectionEnd))
    {
        if (shouldUnselect)
        {
            buffer->place_cursor(selectionEnd);
        }
        operationResult = buffer->get_text(selectionStart, selectionEnd);
    }
}
} // namespace functions
