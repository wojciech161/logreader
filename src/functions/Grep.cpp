#include "Grep.hpp"
#include <iostream>
#include <gtksourceviewmm/buffer.h>
#include "Log.hpp"
#include "Match.hpp"
#include "LogInserter.hpp"

namespace functions
{
Grep::Grep(const model::Log& base, const std::string& query, bool regexp, bool caseSensitive, bool inverted)
: base{base}
, lineMatch{createMatcher(query, regexp, caseSensitive, inverted)} {}

bool Grep::run(model::Log& log) const
{
    const auto& baseBuffer = base.getBuffer();
    auto& targetBuffer = log.getBuffer();
    LogInserter inserter{targetBuffer};
    if (not baseBuffer) return false;
    if (baseBuffer->get_line_count() < 2) return false;
    auto lineBegin = baseBuffer->get_iter_at_line(0);
    try
    {
        for (int i = 1; i <= baseBuffer->get_line_count(); ++i)
        {
            auto lineEnd = baseBuffer->get_iter_at_line(i);
            auto line = baseBuffer->get_text(lineBegin, lineEnd);
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
        return false;
    }
    baseBuffer->place_cursor(baseBuffer->get_iter_at_line(0));
    return true;
}
} // namespace functions
