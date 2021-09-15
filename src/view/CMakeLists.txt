set(SOURCES
    src/ApplicationImpl.cpp
    src/ApplicationFactory.cpp
    src/MainWindow.cpp
    src/MainContainer.cpp
)

set(HEADERS
    include/ApplicationImpl.hpp
    include/MainWindow.hpp
    include/MainContainer.hpp
)

add_library(view ${SOURCES} ${HEADERS})
target_link_libraries(view)
include_directories(view PRIVATE include)