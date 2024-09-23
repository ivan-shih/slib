cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(slib_test
        VERSION 1.0.0.1 # <major>[.<minor>[.<patch>[.<tweak>]]]
)

configure_file(project_config.h.in project_config.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

######## the main source files of this project ########
enable_testing()

add_subdirectory(src)
add_subdirectory(test)

add_test(NAME unit_test COMMAND test/main)
