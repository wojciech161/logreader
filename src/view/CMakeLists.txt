set(SOURCES
    src/ApplicationImpl.cpp
    src/ApplicationFactory.cpp
)

set(HEADERS
    include/ApplicationImpl.hpp
)

add_library(view ${SOURCES} ${HEADERS})
target_link_libraries(view)
include_directories(view PRIVATE include)