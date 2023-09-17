set(
        FORMS
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowController.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/StatusLayoutController.ui
        PARENT_SCOPE
)
add_library(Forms STATIC ${FORMS})