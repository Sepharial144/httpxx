find_package(GTest REQUIRED)
enable_testing()

set(TARGET ${PROJECT_NAME}-unit)

file(GLOB_RECURSE TEST_SRC_FILES "unit/*.cpp")
file(GLOB_RECURSE TEST_HDR_FILES "unit/*.hpp")

add_executable(${TARGET} ${TEST_SRC_FILES} ${TEST_HDR_FILES})

target_link_libraries(${TARGET} PUBLIC GTest::GTest GTest::Main)

target_include_directories(${TARGET} PUBLIC "${HTTPXX_SOURCE_DIR}")