#ifndef BOOST_MP11_SET_HPP_INCLUDED
#define BOOST_MP11_SET_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_set_contains<S, V>
namespace detail
{

template<class S, class V> struct mp_set_contains_impl;

template<template<class...> class L, class... T, class V> struct mp_set_contains_impl<L<T...>, V>
{
    using type = mp_to_bool<std::is_base_of<mp_identity<V>, mp_inherit<mp_identity<T>...> > >;
};

} // namespace detail

template<class S, class V> using mp_set_contains = typename detail::mp_set_contains_impl<S, V>::type;

// mp_set_push_back<S, T...>
namespace detail
{

template<class S, class... T> struct mp_set_push_back_impl;

template<template<class...> class L, class... U> struct mp_set_push_back_impl<L<U...>>
{
    using type = L<U...>;
};

template<template<class...> class L, class... U, template<class...> class L1, class... U1> struct mp_set_push_back_impl<L<U...>, L1<U1...>>
{
    using type = typename mp_set_push_back_impl<L<U...>, U1...>::type;
};

template<template<class...> class L, class... U, class T1, class... T> struct mp_set_push_back_impl<L<U...>, T1, T...>
{
    using S = mp_if<mp_set_contains<L<U...>, T1>, L<U...>, L<U..., T1>>;
    using type = typename mp_set_push_back_impl<S, T...>::type;
};

} // namespace detail

template<class S, class... T> using mp_set_push_back = typename detail::mp_set_push_back_impl<S, T...>::type;

// mp_set_push_front<S, T...>
namespace detail
{

template<class S, class... T> struct mp_set_push_front_impl;

template<template<class...> class L, class... U> struct mp_set_push_front_impl<L<U...>>
{
    using type = L<U...>;
};

template<template<class...> class L, class... U, template<class...> class L1, class... U1> struct mp_set_push_front_impl<L<U...>, L1<U1...>>
{
    using type = typename mp_set_push_front_impl<L<U...>, U1...>::type;
};

template<template<class...> class L, class... U, class T1> struct mp_set_push_front_impl<L<U...>, T1>
{
    using type = mp_if<mp_set_contains<L<U...>, T1>, L<U...>, L<T1, U...>>;
};

template<template<class...> class L, class... U, class T1, class... T> struct mp_set_push_front_impl<L<U...>, T1, T...>
{
    using S = typename mp_set_push_front_impl<L<U...>, T...>::type;
    using type = typename mp_set_push_front_impl<S, T1>::type;
};

} // namespace detail

template<class S, class... T> using mp_set_push_front = typename detail::mp_set_push_front_impl<S, T...>::type;

// mp_is_set<S>
namespace detail
{

template<class S> struct mp_is_set_impl
{
    using type = mp_false;
};

template<template<class...> class L, class... T> struct mp_is_set_impl<L<T...>>
{
    using type = mp_to_bool<std::is_same<mp_list<T...>, mp_set_push_back<mp_list<>, T...> > >;
};

} // namespace detail

template<class S> using mp_is_set = typename detail::mp_is_set_impl<S>::type;

// mp_set_intersection
namespace detail
{
template<class S, class... T> struct mp_set_difference_impl;

template<template<class...> class L, class... U> struct mp_set_difference_impl<L<U...>>
{
    using type = L<U...>;
};

template<class S, class L, class... T> struct mp_set_difference_impl<S, L, T...>
{
    template<typename T1> using L_contains_t = mp_contains<L, T1>;
    using S_prime = mp_remove_if<S, L_contains_t>;
    using type = typename mp_set_difference_impl<mp_cond<
                                                 mp_or<mp_empty<S>, mp_same<S, L>>, mp_clear<S>,
                                                 mp_empty<L>, S,
                                                 mp_true,
                                                 S_prime>, T...>::type;
};

} // namespace detail

template<class S, class... T> using mp_set_difference = typename detail::mp_set_difference_impl<S, T...>::type;

// mp_set_union
template<class S, class... T> using mp_set_union = mp_set_push_back<S, T...>;

// mp_set_intersection
template<class S, class... T> using mp_set_intersection = mp_set_difference<S, mp_set_difference<S, T...>>;

// mp_set_symmetric_difference
template<class S, class... T> using mp_set_symmetric_difference = mp_set_union<mp_set_difference<S, T...>, mp_front<mp_set_difference<mp_reverse<mp_list<S, T...>>>>>;

// mp_intersection
} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_SET_HPP_INCLUDED
