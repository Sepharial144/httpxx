cmake_minimum_required (VERSION 3.20)
project (httpxx)

set(CXX_STANDARD 17)

file(GLOB SRC_FILES "source/*.cpp")
file(GLOB HDR_FILES "source/*.hpp")


set(HTTPXX_SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")

add_subdirectory(tests)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES})
