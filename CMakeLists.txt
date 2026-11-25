cmake_minimum_required(VERSION 4.0)

# CMake 4.3+ UUID for experimental 'import std;' support
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")

# Keep C++23 at project() time so CMake's compiler probe and import std succeed
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("Tachyon" LANGUAGES CXX)

include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark
  GIT_TAG        v1.9.1
)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)

FetchContent_MakeAvailable(benchmark Catch2)

# Gather all sources and modules automatically
file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
list(FILTER SRC_SOURCES EXCLUDE REGEX "src/main\\.cpp$")

file(GLOB_RECURSE TOOL_SOURCES CONFIGURE_DEPENDS "tools/*.cpp")
file(GLOB_RECURSE TOOL_MODULES CONFIGURE_DEPENDS "tools/*.ixx")
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "test/*.cpp")
file(GLOB_RECURSE BENCH_SOURCES CONFIGURE_DEPENDS "bench/*.cpp")

# Shared core library (compiles src and tools once, exposes C++ modules)
add_library(TachyonCore STATIC ${SRC_SOURCES} ${TOOL_SOURCES})
if(TOOL_MODULES)
    target_sources(TachyonCore PUBLIC FILE_SET CXX_MODULES FILES ${TOOL_MODULES})
endif()

# Main executable
add_executable(Tachyon "src/main.cpp")
target_link_libraries(Tachyon PRIVATE TachyonCore)

# Benchmarks
add_executable(TachyonBenchMark ${BENCH_SOURCES})
target_link_libraries(TachyonBenchMark PRIVATE TachyonCore benchmark::benchmark_main)

# Tests
add_executable(TachyonTests ${TEST_SOURCES})
target_link_libraries(TachyonTests PRIVATE TachyonCore Catch2::Catch2WithMain)

# Custom run commands
add_custom_target(run-app
    COMMAND Tachyon
    DEPENDS Tachyon
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Tachyon..."
)

add_custom_target(run-tests
    COMMAND TachyonTests
    DEPENDS TachyonTests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Catch2 tests..."
)

add_custom_target(run-benchmark
    COMMAND TachyonBenchMark
    DEPENDS TachyonBenchMark
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Google Benchmarks..."
)