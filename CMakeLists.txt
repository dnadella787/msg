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

# ---- Fetch Abseil (required for gRPC) ----
FetchContent_Declare(
        abseil
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
        GIT_TAG 20250512.1
)
set(ABSL_PROPAGATE_CXX_STD ON CACHE BOOL "" FORCE)
set(ABSL_ENABLE_INSTALL ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(abseil)

# ---- Fetch gRPC ----
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG v1.74.1
)
FetchContent_MakeAvailable(gRPC)

# Find all protobuf and gRPC generated files to build lib
file(GLOB PROTO_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.pb.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.grpc.pb.cc"
)

file(GLOB PROTO_HDRS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.pb.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.grpc.pb.h"
)

add_executable(msg src/main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(msg PRIVATE spdlog CLI11 grpc++)