set(SOURCES
    src/ApplicationImpl.cpp
    src/ApplicationFactory.cpp
    src/MainWindow.cpp
)

set(HEADERS
    include/ApplicationImpl.hpp
    include/MainWindow.hpp
)

add_library(view ${SOURCES} ${HEADERS})
target_link_libraries(view)
include_directories(view PRIVATE include)