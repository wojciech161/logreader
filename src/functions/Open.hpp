#pragma once

#include <string>
#include "BufferCreator.hpp"

namespace functions
{
class Open : public BufferCreator
{
public:
    Open(const std::string&);
    virtual ~Open() = default;
    virtual Glib::RefPtr<Gsv::Buffer> createBuffer() const override;
    virtual std::string getName() const override;

private:
    std::string path;
};
} // namespace functions
