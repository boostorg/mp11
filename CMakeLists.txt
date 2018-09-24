cmake_minimum_required(VERSION 3.1)

project(BoostMp11 VERSION 1.66.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(mp11 INTERFACE)
add_library(Boost::mp11 ALIAS mp11)

target_include_directories(mp11 INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if (BUILD_TESTING)
    find_package(Boost 1.56 REQUIRED)  # 1.56+ for lightweight_test

    file(GLOB TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)

    foreach(TEST_SRC ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
        set(TEST_NAME "test-${TEST_NAME}")

        message(STATUS "Add test: ${TEST_NAME}")

        add_executable(${TEST_NAME} ${TEST_SRC})

        # Note that local mp11 include path must be before the Boost one,
        # otherwise mp11 headers bundled with Boost (if any) are included.
        target_include_directories(${TEST_NAME} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
            ${Boost_INCLUDE_DIRS}
        )

        target_link_libraries(${TEST_NAME} PRIVATE mp11 ${Boost_LIBRARIES})

        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
endif()

write_basic_package_version_file("${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake" COMPATIBILITY AnyNewerVersion)

install(TARGETS mp11 EXPORT ${CMAKE_PROJECT_NAME})
install(DIRECTORY include/boost/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/boost)
install(FILES "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake" DESTINATION cmake)
install(EXPORT ${CMAKE_PROJECT_NAME} DESTINATION cmake NAMESPACE Boost:: FILE ${CMAKE_PROJECT_NAME}Config.cmake)
export(EXPORT ${CMAKE_PROJECT_NAME} NAMESPACE Boost:: FILE ${CMAKE_PROJECT_NAME}Config.cmake)
