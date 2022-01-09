#pragma once

#include <string>
#include <gtksourceviewmm/buffer.h>

namespace functions
{
class BufferCreator
{
public:
    virtual ~BufferCreator() = default;
    virtual Glib::RefPtr<Gsv::Buffer> createBuffer() const = 0;
    virtual std::string getName() const = 0;
};
} // namespace functions
