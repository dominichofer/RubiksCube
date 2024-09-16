cmake_minimum_required(VERSION 3.18)
project(rubikscube LANGUAGES CXX)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
    set(CMAKE_CXX_FLAGS "/std:c++latest /EHsc /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "/Ox /MD /GL")
else()
    set(CMAKE_CXX_FLAGS "-march=native -w")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

include(FetchContent)

# Google Test
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Google Benchmark
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.5
)
FetchContent_MakeAvailable(googlebenchmark)

# OpenMP
find_package(OpenMP)
link_libraries(OpenMP::OpenMP_CXX)

# if (NOT SKBUILD)
#   message(WARNING "\
#   This CMake file is meant to be executed using 'scikit-build'. Running
#   it directly will almost certainly not produce the desired result. If
#   you are a user trying to install this package, please use the command
#   below, which will install all necessary build dependencies, compile
#   the package in an isolated environment, and then install it.
#   =====================================================================
#    $ pip install .
#   =====================================================================
#   If you are a software developer, and this is your own package, then
#   it is usually much more efficient to install the build dependencies
#   in your environment once and use the following command that avoids
#   a costly creation of a new virtual environment at every compilation:
#   =====================================================================
#    $ pip install nanobind scikit-build-core[pyproject]
#    $ pip install --no-build-isolation -ve .
#   =====================================================================
#   You may optionally add -Ceditable.rebuild=true to auto-rebuild when
#   the package is imported. Otherwise, you need to re-run the above
#   after editing C++ files.")
# endif()

# # Try to import all Python components potentially needed by nanobind
# find_package(Python 3.10
#   REQUIRED COMPONENTS Interpreter Development.Module
#   OPTIONAL_COMPONENTS Development.SABIModule)

# # Import nanobind through CMake's find_package mechanism
# find_package(nanobind CONFIG REQUIRED)

# # We are now ready to compile the actual extension module
# nanobind_add_module(
#   # Name of the extension
#   rubikscube_ext

#   # Target the stable ABI for Python 3.12+, which reduces
#   # the number of binary wheels that must be built. This
#   # does nothing on older Python versions
#   STABLE_ABI

#   # Build libnanobind statically and merge it into the
#   # extension (which itself remains a shared library)
#   #
#   # If your project builds multiple extensions, you can
#   # replace this flag by NB_SHARED to conserve space by
#   # reusing a shared libnanobind across libraries
#   NB_STATIC

#   # Source code goes here
#   src/rubikscube_ext.cpp
# )

add_subdirectory(src/cpp)
add_subdirectory(tests/cpp)

# Install directive for scikit-build-core
# install(TARGETS rubikscube_ext LIBRARY DESTINATION rubikscube)
