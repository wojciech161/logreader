#pragma once

#include <functional>
#include <string>
#include "BufferCreator.hpp"

namespace functions
{
class Grep : public BufferCreator
{
public:
    Grep(const std::string&, bool, bool, bool);
    virtual ~Grep() = default;

    Glib::RefPtr<Gsv::Buffer> createBuffer() const override;
    std::string getName() const override;
    void setBase(const Glib::RefPtr<Gsv::Buffer>&);

private:
    std::function<bool(const std::string&)> lineMatch;
    std::string name;
    Glib::RefPtr<Gsv::Buffer> base;
    
};
} // namespace functions
