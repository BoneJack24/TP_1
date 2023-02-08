set(TEST_SOURCES testsTP_1.cpp ${PROJECT_SOURCE_DIR}/Regle.cpp ${PROJECT_SOURCE_DIR}/SystemeExpert.cpp)

add_executable(
        testsTP_1
        ${TEST_SOURCES}
)

target_include_directories(testsTP_1 PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        testsTP_1
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(testsTP_1)