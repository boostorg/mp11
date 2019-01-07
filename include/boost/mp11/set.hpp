#ifndef BOOST_MP11_SET_HPP_INCLUDED
#define BOOST_MP11_SET_HPP_INCLUDED

// Copyright 2015, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
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

// mp_set_union<L...>
namespace detail
{

template<class... L> struct mp_set_union_impl
{
};

template<> struct mp_set_union_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_set_union_impl<L<T...>>
{
    using type = L<T...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_set_union_impl<L1<T1...>, L2<T2...>>
{
    using type = mp_set_push_back<L1<T1...>, T2...>;
};

template<class L1, class... L> using mp_set_union_ = typename mp_set_union_impl<L1, mp_append<mp_list<>, L...>>::type;

template<class L1, class L2, class L3, class... L> struct mp_set_union_impl<L1, L2, L3, L...>: mp_defer<mp_set_union_, L1, L2, L3, L...>
{
};

} // namespace detail

template<class... L> using mp_set_union = typename detail::mp_set_union_impl<L...>::type;

// mp_set_difference<L...>
namespace detail
{

template<class... L> struct mp_set_difference_impl
{
};

template<> struct mp_set_difference_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_set_difference_impl<L<T...>>
{
    using type = L<T...>;
};


template<template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_set_difference_impl<L1<T1...>, L2<T2...>>
{
    template<class V>
    using predicate_t = mp_contains<L2<T2...>, V>;
    using type = mp_remove_if<L1<T1...>, predicate_t>;
};


template<class L1, class... L> using mp_set_difference_ = typename mp_set_difference_impl<L1, mp_append<mp_list<>, L...>>::type;

template<class L1, class... L> struct mp_set_difference_impl<L1, L...> : mp_defer<mp_set_difference_, L1, L...>
{
};

} // namespace detail

template<class... L> using mp_set_difference = typename detail::mp_set_difference_impl<L...>::type;

// mp_set_intersection<L...>
namespace detail
{

template<class... L> struct mp_set_intersection_impl
{
};

template<> struct mp_set_intersection_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_set_intersection_impl<L<T...>>
{
    using type = L<T...>;
};


template<template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_set_intersection_impl<L1<T1...>, L2<T2...>>
{
    template<class V>
    using predicate_t = mp_contains<L2<T2...>, V>;
    using type = mp_copy_if<L1<T1...>, predicate_t>;
};


template<class L1, class... L> using mp_set_intersection_ = typename mp_set_intersection_impl<L1, mp_append<mp_list<>, L...>>::type;

template<class L1, class... L> struct mp_set_intersection_impl<L1, L...> : mp_defer<mp_set_intersection_, L1, L...>
{
};

} // namespace detail

template<class... L> using mp_set_intersection = typename detail::mp_set_intersection_impl<L...>::type;

// mp_set_symmetric_difference<L...>
namespace detail
{

template<class... L> struct mp_set_symmetric_difference_impl
{
};

template<> struct mp_set_symmetric_difference_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_set_symmetric_difference_impl<L<T...>>
{
    using type = L<>;
};


template<template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_set_symmetric_difference_impl<L1<T1...>, L2<T2...>>
{
    using type = mp_set_union<mp_set_difference<L1<T1...>, L2<T2...>>, mp_set_difference<L2<T2...>, L1<T1...>>>;
};


template<class L1, class... L> using mp_set_symmetric_difference_ = typename mp_set_symmetric_difference_impl<L1, mp_append<mp_list<>, L...>>::type;

template<class L1, class... L> struct mp_set_symmetric_difference_impl<L1, L...> : mp_defer<mp_set_symmetric_difference_, L1, L...>
{
};

} // namespace detail
template<class... L> using mp_set_symmetric_difference = typename detail::mp_set_symmetric_difference_impl<L...>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_SET_HPP_INCLUDED
