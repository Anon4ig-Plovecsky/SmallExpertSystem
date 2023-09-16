set(
        HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowController.h
        PARENT_SCOPE
)
add_library(Headers STATIC ${HEADERS})
set_target_properties(Headers PROPERTIES LINKER_LIST CXX)