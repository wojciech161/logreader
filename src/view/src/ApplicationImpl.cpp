#include "ApplicationImpl.hpp"

namespace view
{
ApplicationImpl::ApplicationImpl(int argc, char** argv)
: app{Gtk::Application::create(argc, argv, "pl.wojciech161.logviewer")}
{
}

int ApplicationImpl::run()
{
    return app->run(window);
}
} // namespace view
