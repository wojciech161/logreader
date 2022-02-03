#pragma once

namespace logic
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
} // namespace logic
