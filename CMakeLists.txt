cmake_minimum_required (VERSION 3.8)
project(draw-function-graph)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
aux_source_directory(src sources)
list(REMOVE_ITEM sources "src/Test.cpp")
add_executable(main ${sources})
set_target_properties(main PROPERTIES CXX_STANDARD 17)
target_link_libraries(main ${SFML_LIBRARIES})

target_compile_options(main PUBLIC -Wall -Wextra -Wconversion -pedantic)

option(BUILD_TESTS "Build unit tests with catch")

if(BUILD_TESTS)
    aux_source_directory(src test_sources)
    list(REMOVE_ITEM test_sources "src/Main.cpp")
    add_executable(tests ${test_sources})

    set_target_properties(tests PROPERTIES CXX_STANDARD 17)
    target_link_libraries(tests ${SFML_LIBRARIES})

    target_compile_options(tests PUBLIC -Wall -Wextra -Wconversion -pedantic)
endif()
