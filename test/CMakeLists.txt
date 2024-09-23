cmake_minimum_required(VERSION 3.10)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

######## make executable ########
add_executable(main
    main.cpp
    testMem.cpp
)

target_include_directories(main PRIVATE
    "${PROJECT_BINARY_DIR}/src"
    $<TARGET_PROPERTY:object_lib,INTERFACE_INCLUDE_DIRECTORIES>
)

target_compile_options(main PRIVATE
    -g -fsanitize=address -fno-elide-constructors -finput-charset=UTF-8 -MMD -MP
)

target_link_libraries(main PRIVATE
    $<TARGET_OBJECTS:object_lib>
    gtest_main
    -fsanitize=address
)
