cmake_minimum_required(VERSION 3.31)
project(msg)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.15.3
)
FetchContent_Declare(
        CLI11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.5.0
)

FetchContent_MakeAvailable(spdlog CLI11)

add_executable(msg main.cpp)
target_link_libraries(msg PRIVATE spdlog CLI11)