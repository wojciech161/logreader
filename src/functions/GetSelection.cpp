#include "GetSelection.hpp"
#include <gtksourceviewmm/buffer.h>
#include "Log.hpp"

namespace functions
{
GetSelection::GetSelection(std::string& result, bool shouldUnselect)
: operationResult{result}
, shouldUnselect{shouldUnselect}
{
}

bool GetSelection::run(model::Log& log) const
{
    const auto& buffer{log.getBuffer()};
    Gtk::TextIter selectionStart, selectionEnd;
    if (buffer->get_selection_bounds(selectionStart, selectionEnd))
    {
        if (shouldUnselect)
        {
            buffer->place_cursor(selectionEnd);
        }
        operationResult = buffer->get_text(selectionStart, selectionEnd);
        return true;
    }
    return false;
}
} // namespace functions
