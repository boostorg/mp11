#ifndef BOOST_MP11_FUNCTION_HPP_INCLUDED
#define BOOST_MP11_FUNCTION_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_plus.hpp>

namespace boost
{

// mp_not<T>
template<class T> using mp_not = mp_bool< !T::value >;

// mp_equal_to<T1, T2>
template<class T1, class T2> using mp_equal_to = mp_bool< T1::value == T2::value >;

// mp_all<T...>
// mp_and<T...>
// mp_any<T...>
// mp_or<T...>

} // namespace boost

#endif // #ifndef BOOST_MP11_FUNCTION_HPP_INCLUDED
