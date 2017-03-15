#ifndef BOOST_MP11_MAP_HPP_INCLUDED
#define BOOST_MP11_MAP_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_map_find.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/algorithm.hpp>
#include <type_traits>

namespace boost
{

// mp_map_contains<M, K>
template<class M, class K> using mp_map_contains = mp_not<std::is_same<mp_map_find<M, K>, void>>;

// mp_map_insert<M, T>
template<class M, class T> using mp_map_insert = mp_if< mp_map_contains<M, mp_first<T>>, M, mp_push_back<M, T> >;

// mp_map_replace<M, T>
namespace detail
{

template<class M, class T> struct mp_map_replace_impl;

template<template<class...> class M, class... U, class T> struct mp_map_replace_impl<M<U...>, T>
{
    using K = mp_first<T>;

    // mp_replace_if is inlined here using a struct _f because of msvc-14.0

    template<class V> struct _f { using type = mp_if< std::is_same<mp_first<V>, K>, T, V >; };

    using type = mp_if< mp_map_contains<M<U...>, K>, M<typename _f<U>::type...>, M<U..., T> >;
};

} // namespace detail

template<class M, class T> using mp_map_replace = typename detail::mp_map_replace_impl<M, T>::type;

// mp_map_update<M, T, F>
namespace detail
{

template<class M, class T, template<class...> class F> struct mp_map_update_impl
{
    template<class U> using _f = std::is_same<mp_first<T>, mp_first<U>>;

    // _f3<L<X, Y...>> -> L<X, F<X, Y...>>
    template<class L> using _f3 = mp_assign<L, mp_list<mp_first<L>, mp_rename<L, F>>>;

    using type = mp_if< mp_map_contains<M, mp_first<T>>, mp_transform_if<_f, _f3, M>, mp_push_back<M, T> >;
};

} // namespace detail

template<class M, class T, template<class...> class F> using mp_map_update = typename detail::mp_map_update_impl<M, T, F>::type;

// mp_map_erase<M, K>
namespace detail
{

template<class M, class K> struct mp_map_erase_impl
{
    template<class T> using _f = std::is_same<mp_first<T>, K>;
    using type = mp_remove_if<M, _f>;
};

} // namespace detail

template<class M, class K> using mp_map_erase = typename detail::mp_map_erase_impl<M, K>::type;

} // namespace boost

#endif // #ifndef BOOST_MP11_MAP_HPP_INCLUDED
