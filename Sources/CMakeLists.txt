set(
        SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StatusLayoutController.cpp
        PARENT_SCOPE
)
add_library(Sources STATIC ${SOURCES})