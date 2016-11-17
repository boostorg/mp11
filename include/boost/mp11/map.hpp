#ifndef BOOST_MP11_MAP_HPP_INCLUDED
#define BOOST_MP11_MAP_HPP_INCLUDED

//  Copyright 2015, 2016 Peter Dimov.
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
// mp_map_erase<M, K>

} // namespace boost

#endif // #ifndef BOOST_MP11_MAP_HPP_INCLUDED
