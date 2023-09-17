set(
        SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StatusLayoutController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/KnowledgeBaseController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Outcome.cpp
        PARENT_SCOPE
)
add_library(Sources STATIC ${SOURCES})