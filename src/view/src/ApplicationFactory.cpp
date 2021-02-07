#include "view/ApplicationFactory.hpp"
#include "ApplicationImpl.hpp"

namespace view
{
std::unique_ptr<Application> create_application(int argc, char** argv)
{
    return std::make_unique<ApplicationImpl>(argc, argv);
}
} // namespace view
