# Copyright 2018 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.5...3.16)

project(boost_mp11 VERSION 1.73.0 LANGUAGES CXX)

add_library(boost_mp11 INTERFACE)
set_property(TARGET boost_mp11 PROPERTY EXPORT_NAME mp11)

add_library(Boost::mp11 ALIAS boost_mp11)

target_include_directories(boost_mp11 INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_compile_features(boost_mp11 INTERFACE cxx_alias_templates cxx_variadic_templates cxx_decltype)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

    # Testing

    include(CTest)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG>)

    include(BoostFetch)

    set(BUILD_TESTING OFF)

    boost_fetch(boostorg/assert TAG develop EXCLUDE_FROM_ALL)
    boost_fetch(boostorg/config TAG develop EXCLUDE_FROM_ALL)
    boost_fetch(boostorg/core TAG develop EXCLUDE_FROM_ALL)

    unset(BUILD_TESTING)

    # Installation

    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    set(LIB boost_mp11)
    set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB}-${PROJECT_VERSION})

    install(TARGETS ${LIB} EXPORT ${LIB}-targets)
    install(EXPORT ${LIB}-targets DESTINATION ${CONFIG_INSTALL_DIR} NAMESPACE Boost:: FILE ${LIB}-config.cmake)

    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # Mp11 is independent of 32/64, so this hack makes BoostMp11ConfigVersion.cmake skip the check
    set(OLD_CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})
    unset(CMAKE_SIZEOF_VOID_P)
    write_basic_package_version_file("${PROJECT_BINARY_DIR}/${LIB}-config-version.cmake" COMPATIBILITY AnyNewerVersion)
    set(CMAKE_SIZEOF_VOID_P ${OLD_CMAKE_SIZEOF_VOID_P})

    install(FILES "${PROJECT_BINARY_DIR}/${LIB}-config-version.cmake" DESTINATION ${CONFIG_INSTALL_DIR})

    #export(EXPORT ${PROJECT_NAME}Targets NAMESPACE Boost:: FILE ${PROJECT_NAME}Config.cmake)

endif()

if(BUILD_TESTING)

    add_subdirectory(test)

endif()
