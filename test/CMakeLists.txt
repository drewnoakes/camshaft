cmake_minimum_required(VERSION 2.8.4)

set(TEST_SOURCES
    unittests.cc

    any_test.cc
    observable_test.cc
    uuid_test.cc

    ../src/demangle.cc
    ../src/observable.cc
    ../src/uuid.cc

    google-test/src/gtest-all.cc
)

#
## Target for running tests (custom targets are always run)
#
add_custom_target(camshaft-runtests
    ALL ./camshaft-unittests
    DEPENDS camshaft-unittests)

#
## Include directories
#
include_directories(SYSTEM google-test/include)
include_directories(google-test)

#
## Target
#
add_executable(camshaft-unittests
  ${TEST_SOURCES}
)

#
## Link executable to libraries
#
target_link_libraries(camshaft-unittests pthread uuid)
