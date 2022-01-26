#pragma once

namespace controller
{
class Controller
{
public:
    Controller() = default;
    ~Controller() = default;

    void openFile();
    void performGrep();
    void performFind();
    void performMark();
    void performBookmark();
    void performAbout();
};
} // namespace controller
