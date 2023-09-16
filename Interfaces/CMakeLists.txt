set(
        INTERFACES
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowController.ui
        PARENT_SCOPE
)
add_library(Interfaces STATIC ${INTERFACES})