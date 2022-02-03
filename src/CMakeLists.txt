link_directories(
    ${GTKMM_LIBRARY_DIRS}
    ${GTKSOURCEVIEWMM_LIBRARY_DIRS}
)

include_directories(
    ${GTKMM_INCLUDE_DIRS}
    ${GTKSOURCEVIEWMM_INCLUDE_DIRS}
    view
    model
    functions
)

add_executable(
    LogReader

    app/application.cpp

    logic/Controller.cpp

    functions/AddBookmark.cpp
    functions/Find.cpp
    functions/GetSelection.cpp
    functions/Grep.cpp
    functions/LogInserter.cpp
    functions/Mark.cpp
    functions/Match.cpp
    functions/NameCreator.cpp
    functions/OpenSingle.cpp

    model/Bookmark.cpp
    model/BookmarkList.cpp
    model/Log.cpp
    model/LogList.cpp

    view/AboutDialog.cpp
    view/BookmarkDialog.cpp
    view/BookmarkView.cpp
    view/FileChooser.cpp
    view/FindDialog.cpp
    view/GrepDialog.cpp
    view/MarkDialog.cpp
    view/LogContainer.cpp
    view/LogView.cpp
    view/MainWindow.cpp
    view/MenuBuilder.cpp
    view/TabLabel.cpp
)

target_link_libraries(LogReader 
    ${GTKMM_LIBRARIES}
    ${GTKSOURCEVIEWMM_LIBRARIES}
)
