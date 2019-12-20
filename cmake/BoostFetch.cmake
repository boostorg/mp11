# Copyright 2018 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

if(NOT COMMAND FetchContent_Populate)

    if(CMAKE_VERSION VERSION_LESS 3.11)

        message(STATUS "Fetching FetchContent.cmake")

        file(DOWNLOAD
            "https://gitlab.kitware.com/cmake/cmake/raw/v3.11.3/Modules/FetchContent.cmake"
            "${CMAKE_BINARY_DIR}/Modules/FetchContent.cmake"
        )

        file(DOWNLOAD
            "https://gitlab.kitware.com/cmake/cmake/raw/v3.11.3/Modules/FetchContent/CMakeLists.cmake.in"
            "${CMAKE_BINARY_DIR}/Modules/FetchContent/CMakeLists.cmake.in"
        )

        include(${CMAKE_BINARY_DIR}/Modules/FetchContent.cmake)

    else()

        include(FetchContent)

    endif()

endif()

function(boost_fetch)

    cmake_parse_arguments(_ "" "TAG" "" ${ARGN})

    if(NOT __UNPARSED_ARGUMENTS)

        message(FATAL_ERROR "boost_fetch: missing required argument, repository name")
        return()

    endif()

    list(GET __UNPARSED_ARGUMENTS 0 REPO)
    list(REMOVE_AT __UNPARSED_ARGUMENTS 0)

    if(__UNPARSED_ARGUMENTS)

        message(WARNING "boost_fetch: extra arguments ignored: ${__UNPARSED_ARGUMENTS}")

    endif()

    if(NOT __TAG)

        set(__TAG master)

    endif()

    string(MAKE_C_IDENTIFIER ${REPO} NAME)

    if(CMAKE_VERSION VERSION_LESS 3.6)

        FetchContent_Declare(${NAME} QUIET GIT_REPOSITORY "https://github.com/${REPO}" GIT_TAG ${__TAG})

    else()

        FetchContent_Declare(${NAME} QUIET GIT_REPOSITORY "https://github.com/${REPO}" GIT_TAG ${__TAG} GIT_SHALLOW 1)

    endif()

    FetchContent_GetProperties(${NAME})

    if(NOT ${NAME}_POPULATED)

        message(STATUS "Fetching ${REPO}:${__TAG}")

        FetchContent_Populate(${NAME})
        add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})

    endif()

endfunction(boost_fetch)
