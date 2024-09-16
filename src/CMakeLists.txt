add_library(object_lib OBJECT
    mem.c
)

target_include_directories(object_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

if (BUILD_TESTS)
    target_compile_options(object_lib PRIVATE
        -g -fsanitize=address -finput-charset=UTF-8 -MMD -MP
    )
endif()
