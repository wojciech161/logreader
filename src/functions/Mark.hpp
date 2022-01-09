#pragma once

#include <string>
#include <gtksourceviewmm/buffer.h>

namespace functions
{
class Mark
{
public:
    Mark(const std::string&);
    ~Mark() = default;

    void run(const Glib::RefPtr<Gsv::Buffer>&);

private:
    std::string query;
};
} // namespace functions
