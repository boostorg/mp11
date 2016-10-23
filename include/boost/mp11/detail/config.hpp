#ifndef BOOST_MP11_DETAIL_CONFIG_HPP_INCLUDED
#define BOOST_MP11_DETAIL_CONFIG_HPP_INCLUDED

//  Copyright 2016 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if defined( BOOST_NO_CXX11_CONSTEXPR )

#  define BOOST_MP11_NO_CONSTEXPR

#elif defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1900 )

#  define BOOST_MP11_NO_CONSTEXPR

#endif

#endif // #ifndef BOOST_MP11_DETAIL_CONFIG_HPP_INCLUDED
