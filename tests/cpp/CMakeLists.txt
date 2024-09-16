include_directories(${CMAKE_SOURCE_DIR}/src/cpp)

add_executable(
    RubiksCubeTest
    test_corners.cpp
    test_corner_solution.cpp
    test_intrin.cpp
)

target_link_libraries(
    RubiksCubeTest
    RubiksCube
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(RubiksCubeTest)