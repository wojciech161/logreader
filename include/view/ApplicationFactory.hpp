#pragma once

#include <memory>

namespace view
{
class Application;
} // namespace view

namespace view
{
std::unique_ptr<Application> create_application(int, char**);
} // namespace view
