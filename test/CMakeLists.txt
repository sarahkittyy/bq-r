project(bq-r)

find_package(Catch2 REQUIRED)

file(GLOB_RECURSE sources "*.cpp")
add_executable(bq-r-test ${sources})
add_dependencies(bq-r-test bq-r-test-lib)
target_link_libraries(bq-r-test bq-r-test-lib Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(bq-r-test)
