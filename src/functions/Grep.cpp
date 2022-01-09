#include "Grep.hpp"
#include <exception>
#include <iostream>
#include "Match.hpp"
#include "LogInserter.hpp"

namespace
{
std::string createName(const std::string& query, bool regexp, bool caseSensitive, bool inverted)
{
    std::string options{"."};
    options += regexp ? "R" : "r";
    options += caseSensitive ? "C" : "c";
    options += inverted ? "I" : "i";
    return query + options;
}
} // namespace

namespace functions
{
Grep::Grep(const std::string& query, bool regexp, bool caseSensitive, bool inverted)
: lineMatch{createMatcher(query, regexp, caseSensitive, inverted)}
, name{createName(query, regexp, caseSensitive, inverted)} {}

Glib::RefPtr<Gsv::Buffer> Grep::createBuffer() const
{
    Glib::RefPtr<Gsv::Buffer> buffer{Gsv::Buffer::create()};
    LogInserter inserter{buffer};
    if (not base) return buffer;
    if (base->get_line_count() < 2) return buffer;
    auto lineBegin = base->get_iter_at_line(0);
    try
    {
        for (int i = 1; i <= base->get_line_count(); ++i)
        {
            auto lineEnd = base->get_iter_at_line(i);
            auto line = base->get_text(lineBegin, lineEnd);
            if (lineMatch(line.raw()))
            {
                inserter.addLine(line);
            }
            lineBegin = lineEnd;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Error encountered during grep: " << e.what() << std::endl;
    }
    buffer->place_cursor(buffer->get_iter_at_line(0));
    return buffer;
}

std::string Grep::getName() const
{
    return name;
}

void Grep::setBase(const Glib::RefPtr<Gsv::Buffer>& baseBuffer)
{
    base = baseBuffer;
}
} // namespace functions
