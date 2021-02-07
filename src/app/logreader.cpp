#include "view/Application.hpp"
#include "view/ApplicationFactory.hpp"

int main(int argc, char** argv)
{
    auto app = view::create_application(argc, argv);
    return app->run();
}