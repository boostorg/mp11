# Copyright 2018 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.5)

project(BoostMp11 VERSION 1.69.0 LANGUAGES CXX)

add_library(boost_mp11 INTERFACE)
add_library(Boost::mp11 ALIAS boost_mp11)

target_include_directories(boost_mp11 INTERFACE include)
target_compile_features(boost_mp11 INTERFACE cxx_alias_templates cxx_variadic_templates cxx_decltype)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

    # requires CMake 3.11 so we just carry it around
    include(cmake/FetchContent.cmake)

    message("-- Fetching pdimov/mincmake")
    FetchContent_Populate(pdimov_mincmake QUIET GIT_REPOSITORY https://github.com/pdimov/mincmake GIT_TAG master GIT_SHALLOW 1)
    include(${pdimov_mincmake_SOURCE_DIR}/cmake/boost_test.cmake)

    message("-- Fetching boostorg/assert")
    FetchContent_Populate(boostorg_assert QUIET GIT_REPOSITORY https://github.com/boostorg/assert GIT_TAG develop GIT_SHALLOW 1)
    add_subdirectory(${boostorg_assert_SOURCE_DIR} ${boostorg_assert_BINARY_DIR})

    message("-- Fetching boostorg/config")
    FetchContent_Populate(boostorg_config QUIET GIT_REPOSITORY https://github.com/boostorg/config GIT_TAG develop GIT_SHALLOW 1)
    add_subdirectory(${boostorg_config_SOURCE_DIR} ${boostorg_config_BINARY_DIR})

    message("-- Fetching boostorg/core")
    FetchContent_Populate(boostorg_core QUIET GIT_REPOSITORY https://github.com/boostorg/core GIT_TAG develop GIT_SHALLOW 1)
    add_subdirectory(${boostorg_core_SOURCE_DIR} ${boostorg_core_BINARY_DIR})

    enable_testing()

    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG>)

endif()

if(COMMAND boost_test)

    add_subdirectory(test)

endif()
