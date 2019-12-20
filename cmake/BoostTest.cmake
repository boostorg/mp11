# Copyright 2018, 2019 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

function(boost_test)

    cmake_parse_arguments(_ "" "TYPE;PREFIX;NAME" "SOURCES;LIBRARIES;ARGUMENTS" ${ARGN})

    if(NOT __TYPE)
        set(__TYPE run)
    endif()

    if(NOT __PREFIX)
        set(__PREFIX ${PROJECT_NAME})
    endif()

    if(NOT __NAME)
        list(GET __SOURCES 0 __NAME)
        string(MAKE_C_IDENTIFIER ${__NAME} __NAME)
    endif()

    set(__NAME ${__PREFIX}-${__NAME})

    if(__TYPE STREQUAL "compile" OR __TYPE STREQUAL "compile-fail")

        add_library(${__NAME} STATIC EXCLUDE_FROM_ALL ${__SOURCES})
        target_link_libraries(${__NAME} ${__LIBRARIES})

        add_test(NAME compile-${__NAME} COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ${__NAME} --config $<CONFIG>)

        if(__TYPE STREQUAL "compile-fail")
            set_tests_properties(compile-${__NAME} PROPERTIES WILL_FAIL TRUE)
        endif()

    elseif(__TYPE STREQUAL "link")

        add_executable(${__NAME} EXCLUDE_FROM_ALL ${__SOURCES})
        target_link_libraries(${__NAME} ${__LIBRARIES})

        add_test(NAME link-${__NAME} COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ${__NAME} --config $<CONFIG>)

    elseif(__TYPE STREQUAL "link-fail")

        add_library(compile-${__NAME} STATIC EXCLUDE_FROM_ALL ${__SOURCES})
        target_link_libraries(compile-${__NAME} ${__LIBRARIES})

        add_test(NAME compile-${__NAME} COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target compile-${__NAME} --config $<CONFIG>)

        add_executable(${__NAME} EXCLUDE_FROM_ALL ${__SOURCES})
        target_link_libraries(${__NAME} ${__LIBRARIES})

        add_test(NAME link-${__NAME} COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ${__NAME} --config $<CONFIG>)
        set_tests_properties(link-${__NAME} PROPERTIES WILL_FAIL TRUE)

    elseif(__TYPE STREQUAL "run" OR __TYPE STREQUAL "run-fail")

        add_executable(${__NAME} EXCLUDE_FROM_ALL ${__SOURCES})
        target_link_libraries(${__NAME} ${__LIBRARIES})

        add_test(NAME compile-${__NAME} COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ${__NAME} --config $<CONFIG>)

        add_test(NAME run-${__NAME} COMMAND ${__NAME} ${__ARGUMENTS})
        set_tests_properties(run-${__NAME} PROPERTIES DEPENDS compile-${__NAME})

        if(__TYPE STREQUAL "run-fail")
            set_tests_properties(run-${__NAME} PROPERTIES WILL_FAIL TRUE)
        endif()

    endif()

endfunction(boost_test)
