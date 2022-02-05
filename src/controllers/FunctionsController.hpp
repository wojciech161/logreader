#pragma once

#include <string>

namespace view
{
class LogContainer;
class MainWindow;
} // namespace view

namespace controllers
{
class FunctionsController
{
public:
    FunctionsController(view::MainWindow&);
    ~FunctionsController();

    void performGrep() const;
    void performMark() const;
    void performFind() const;

private:
    std::string getSelection(bool souldUnmark = true) const;

private:
    view::MainWindow& appWindow;
    view::LogContainer& fileView;
};
} // namespace controllers
