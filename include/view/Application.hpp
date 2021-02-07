#pragma once

namespace view
{
class Application
{
public:
    virtual ~Application() = default;
    virtual int run() = 0;
};
} // namespace view
