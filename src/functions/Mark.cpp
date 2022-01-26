#include "Mark.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <gtksourceviewmm/buffer.h>
#include "LogView.hpp"

namespace
{
Gdk::RGBA drawColor()
{
    Gdk::RGBA color{};
    std::random_device randomDevice;
    std::default_random_engine engine{randomDevice()};
    std::uniform_int_distribution<gushort> distribution{0, 65535};
    gushort red = distribution(engine);
    gushort green = distribution(engine);
    gushort blue = distribution(engine);
    color.set_rgba_u(red, green, blue);
    return color;
}
} // namespace

namespace functions
{
Mark::Mark(const std::string& q)
: query{q}
{
    std::transform(query.begin(), query.end(), query.begin(),
        [](auto& c) {return std::tolower(c);});
}

void Mark::run(view::LogView& logView) const
{
    const Glib::RefPtr<Gsv::Buffer>& buffer{logView.getBuffer()};
    auto currentTag = buffer->get_tag_table()->lookup(query);
    if (not currentTag)
    {
        std::cout << "Marking: " << query << std::endl;
        auto currentPosition = buffer->get_iter_at_line(0);
        Gtk::TextIter matchStart, matchEnd;
        auto backgroundColorTag = buffer->create_tag(query);
        backgroundColorTag->property_background_rgba() = drawColor();
        while (currentPosition.forward_search(query, Gtk::TEXT_SEARCH_CASE_INSENSITIVE, matchStart, matchEnd))
        {
            buffer->apply_tag(backgroundColorTag, matchStart,matchEnd);
            currentPosition = matchEnd;
        }
    }
    else
    {
        std::cout << "Unmarking: " << query << std::endl;
        buffer->remove_tag(currentTag, buffer->begin(), buffer->end());
        buffer->get_tag_table()->remove(currentTag);
    }
}
} // namespace functions
