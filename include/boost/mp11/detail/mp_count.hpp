#ifndef BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED

//  Copyright 2015, 2016 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_plus.hpp>
#include <boost/mp11/detail/config.hpp>
#include <boost/config.hpp>

namespace boost
{

// mp_count<L, V>
namespace detail
{

template<class L, class V> struct mp_count_impl;

#if !defined( BOOST_MP11_NO_CONSTEXPR )

constexpr std::size_t cx_plus()
{
    return 0;
}

template<class T1, class... T> constexpr std::size_t cx_plus(T1 t1, T... t)
{
    return t1 + cx_plus(t...);
}

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<cx_plus(std::is_same<T, V>::value...)>;
};

#else

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<mp_plus<std::is_same<T, V>...>::value>;
};

#endif

} // namespace detail

template<class L, class V> using mp_count = typename detail::mp_count_impl<L, V>::type;

// mp_count_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_count_if_impl;

#if !defined( BOOST_MP11_NO_CONSTEXPR )

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
    using type = mp_size_t<cx_plus(mp_to_bool<P<T>>::value...)>;
};

#else

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1900 )

    template<class T> struct _f { using type = mp_to_bool<P<T>>; };
    using type = mp_size_t<mp_plus<typename _f<T>::type...>::value>;

#else

    using type = mp_size_t<mp_plus<mp_to_bool<P<T>>...>::value>;

#endif
};

#endif

} // namespace detail

template<class L, template<class...> class P> using mp_count_if = typename detail::mp_count_if_impl<L, P>::type;

} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED
