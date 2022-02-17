#include "LogInserter.hpp"
#include "Match.hpp"

namespace
{
const Gdk::RGBA RED{"#FF0000"};
const Gdk::RGBA BLUE{"#0000FF"};
} // namespace

namespace functions
{
LogInserter::LogInserter(Glib::RefPtr<Gsv::Buffer>& buffer)
: buffer{buffer}
, errorTag{buffer->create_tag("errorLine")}
, warningTag{buffer->create_tag("warningLine")}
, isError{createMatcher("error", false, false, false)}
, isWarning{createMatcher("warn", false, false, false)}
{
    errorTag->property_foreground_rgba() = RED;
    warningTag->property_foreground_rgba() = BLUE;
}

void LogInserter::addLine(const std::string& line)
{
    if (isError(line))
    {
        buffer->insert_with_tag(buffer->end(), line, errorTag);
    }
    else if(isWarning(line))
    {
        buffer->insert_with_tag(buffer->end(), line, warningTag);
    }
    else
    {
        buffer->insert(buffer->end(), line);
    }
}
} // namespace functions
