#pragma once
#include "view/Application.hpp"

namespace view
{
class ApplicationImpl : public Application
{
public:
    ApplicationImpl(int, char**);
    ~ApplicationImpl() override = default;
    int run() override;
};
} // namespace view
