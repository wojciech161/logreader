#pragma once

namespace view
{
class LogContainer;
class MainWindow;
} // namespace view


namespace controllers
{
class BookmarkController
{
public:
    BookmarkController(view::MainWindow&);
    ~BookmarkController();

    void addBookmark() const;

private:
    view::MainWindow& appWindow;
    view::LogContainer& fileView;
};
} // namespace controllers
