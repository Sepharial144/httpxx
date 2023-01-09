cmake_minimum_required (VERSION 3.20)
project (httpxx)

set(CXX_STANDARD 17)

file(GLOB SRC_FILES "source/*.hpp" "source/*.cpp")
file(GLOB_RECURSE ENCODER_SRC_FILES "source/encoder/*.hpp" "source/encoder/*.cpp" "source/Factory.hpp")
file(GLOB_RECURSE DECODER_SRC_FILES "source/decoder/*.hpp" "source/decoder/*.cpp")
file(GLOB_RECURSE VALIDATE_SRC_FILES "source/validate/*.hpp" "source/validate/*.cpp")

message(STATUS "source: ${SRC_FILES} ${HDR_FILES}")
message(STATUS "encoder: ${ENCODER_SRC_FILES}")
message(STATUS "decoder: ${DECODER_SRC_FILES}")

set(HTTPXX_SOURCE_FILES
    ${ENCODER_SRC_FILES}
    ${DECODER_SRC_FILES}
    ${VALIDATE_SRC_FILES}
)

set(HTTPXX_SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")

add_subdirectory(tests)

add_executable(${PROJECT_NAME} ${HTTPXX_SOURCE_FILES} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/source")
