#ifndef BOOST_MP11_FUNCTION_HPP_INCLUDED
#define BOOST_MP11_FUNCTION_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_count.hpp>

namespace boost
{
namespace mp11
{

// mp_all<T...>
template<class... T> using mp_all = mp_bool< mp_count_if< mp_list<T...>, mp_to_bool >::value == sizeof...(T) >;

// mp_and<T...>
namespace detail
{

template<class... T> struct mp_and_impl;

} // namespace detail

template<class... T> using mp_and = typename detail::mp_and_impl<T...>::type;

namespace detail
{

template<> struct mp_and_impl<>
{
    using type = mp_true;
};

template<class T> struct mp_and_impl<T>
{
    using type = T;
};

template<class T1, class... T> struct mp_and_impl<T1, T...>
{
    using type = mp_eval_if< mp_not<T1>, T1, mp_and, T... >;
};

} // namespace detail

// mp_any<T...>
template<class... T> using mp_any = mp_bool< mp_count_if< mp_list<T...>, mp_to_bool >::value != 0 >;

// mp_or<T...>
namespace detail
{

template<class... T> struct mp_or_impl;

} // namespace detail

template<class... T> using mp_or = typename detail::mp_or_impl<T...>::type;

namespace detail
{

template<> struct mp_or_impl<>
{
    using type = mp_false;
};

template<class T> struct mp_or_impl<T>
{
    using type = T;
};

template<class T1, class... T> struct mp_or_impl<T1, T...>
{
    using type = mp_eval_if< T1, T1, mp_or, T... >;
};

} // namespace detail

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_FUNCTION_HPP_INCLUDED
