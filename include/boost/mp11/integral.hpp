#ifndef BOOST_MP11_INTEGRAL_HPP_INCLUDED
#define BOOST_MP11_INTEGRAL_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/version.hpp>
#include <boost/mp11/detail/mp_value.hpp>
#include <boost/mp11/detail/config.hpp>
#include <boost/mp11/detail/modules.hpp>
#ifndef BOOST_USE_MODULES
#include <type_traits>
#include <cstddef>
#endif

#if defined(_MSC_VER) || defined(__GNUC__)
# pragma push_macro( "I" )
# undef I
#endif

namespace boost
{
namespace mp11
{

// mp_bool
BOOST_MODULE_EXPORT template<bool B> using mp_bool = std::integral_constant<bool, B>;

BOOST_MODULE_EXPORT using mp_true = mp_bool<true>;
BOOST_MODULE_EXPORT using mp_false = mp_bool<false>;

// mp_to_bool
BOOST_MODULE_EXPORT template<class T> using mp_to_bool = mp_bool<static_cast<bool>( T::value )>;

// mp_not<T>
BOOST_MODULE_EXPORT template<class T> using mp_not = mp_bool< !T::value >;

// mp_int
BOOST_MODULE_EXPORT template<int I> using mp_int = std::integral_constant<int, I>;

// mp_size_t
BOOST_MODULE_EXPORT template<std::size_t N> using mp_size_t = std::integral_constant<std::size_t, N>;

} // namespace mp11
} // namespace boost

#if defined(_MSC_VER) || defined(__GNUC__)
# pragma pop_macro( "I" )
#endif

#endif // #ifndef BOOST_MP11_INTEGRAL_HPP_INCLUDED
