find_package(GTest REQUIRED)
enable_testing()

set(TARGET ${PROJECT_NAME}-unit)

file(GLOB_RECURSE TEST_SRC_FILES "unit/*.hpp" "unit/*.cpp")

add_executable(${TARGET} ${TEST_SRC_FILES} ${HTTPXX_SOURCE_FILES})

target_link_libraries(${TARGET} PUBLIC GTest::GTest GTest::Main)

target_include_directories(${TARGET} PUBLIC "${CMAKE_SOURCE_DIR}/source")