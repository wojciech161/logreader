#include "ApplicationController.hpp"

int main(int argc, char *argv[])
{
    controllers::ApplicationController appController{argc, argv};
    return appController.run();
}
