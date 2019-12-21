# Copyright 2019 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

if(NOT CMAKE_VERSION VERSION_LESS 3.10)
  include_guard()
endif()

function(boost_message type)

  if(type STREQUAL "VERBOSE")
    if(Boost_VERBOSE OR Boost_DEBUG)
      set(type STATUS)
    elseif(CMAKE_VERSION VERSION_LESS 3.15)
      return()
    endif()
  endif()

  if(type STREQUAL "DEBUG")
    if(Boost_DEBUG)
      set(type STATUS)
    elseif(CMAKE_VERSION VERSION_LESS 3.15)
      return()
    endif()
  endif()

  set(m "")
  math(EXPR last "${ARGC}-1")

  foreach(i RANGE 1 ${last})
    set(m "${m}${ARGV${i}}")
  endforeach()

  message(${type} "${m}")

endfunction()
