#ifndef BOOST_MP11_LIST_HPP_INCLUDED
#define BOOST_MP11_LIST_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

namespace boost
{
namespace mp11
{

// mp_size<L>
namespace detail
{

template<class L> struct mp_size_impl;

template<template<class...> class L, class... T> struct mp_size_impl<L<T...>>
{
    using type = mp_size_t<sizeof...(T)>;
};

} // namespace detail

template<class L> using mp_size = typename detail::mp_size_impl<L>::type;

// mp_empty<L>
template<class L> using mp_empty = mp_bool< mp_size<L>::value == 0 >;

// mp_front<L>
namespace detail
{

template<class L> struct mp_front_impl;

template<template<class...> class L, class T1, class... T> struct mp_front_impl<L<T1, T...>>
{
    using type = T1;
};

} // namespace detail

template<class L> using mp_front = typename detail::mp_front_impl<L>::type;

// mp_pop_front<L>
namespace detail
{

template<class L> struct mp_pop_front_impl;

template<template<class...> class L, class T1, class... T> struct mp_pop_front_impl<L<T1, T...>>
{
    using type = L<T...>;
};

} // namespace detail

template<class L> using mp_pop_front = typename detail::mp_pop_front_impl<L>::type;

// mp_first<L>
template<class L> using mp_first = mp_front<L>;

// mp_rest<L>
template<class L> using mp_rest = mp_pop_front<L>;

// mp_second<L>
namespace detail
{

template<class L> struct mp_second_impl;

template<template<class...> class L, class T1, class T2, class... T> struct mp_second_impl<L<T1, T2, T...>>
{
    using type = T2;
};

} // namespace detail

template<class L> using mp_second = typename detail::mp_second_impl<L>::type;

// mp_third<L>
namespace detail
{

template<class L> struct mp_third_impl;

template<template<class...> class L, class T1, class T2, class T3, class... T> struct mp_third_impl<L<T1, T2, T3, T...>>
{
    using type = T3;
};

} // namespace detail

template<class L> using mp_third = typename detail::mp_third_impl<L>::type;

// mp_push_front<L, T...>
namespace detail
{

template<class L, class... T> struct mp_push_front_impl;

template<template<class...> class L, class... U, class... T> struct mp_push_front_impl<L<U...>, T...>
{
    using type = L<T..., U...>;
};

} // namespace detail

template<class L, class... T> using mp_push_front = typename detail::mp_push_front_impl<L, T...>::type;

// mp_push_back<L, T...>
namespace detail
{

template<class L, class... T> struct mp_push_back_impl;

template<template<class...> class L, class... U, class... T> struct mp_push_back_impl<L<U...>, T...>
{
    using type = L<U..., T...>;
};

} // namespace detail

template<class L, class... T> using mp_push_back = typename detail::mp_push_back_impl<L, T...>::type;

// mp_rename<L, B>
namespace detail
{

template<class A, template<class...> class B> struct mp_rename_impl;

template<template<class...> class A, class... T, template<class...> class B> struct mp_rename_impl<A<T...>, B>
{
    using type = B<T...>;
};

} // namespace detail

template<class A, template<class...> class B> using mp_rename = typename detail::mp_rename_impl<A, B>::type;

template<template<class...> class F, class L> using mp_apply = typename detail::mp_rename_impl<L, F>::type;

// mp_append<L...>
namespace detail
{

template<class... L> struct mp_append_impl;

template<> struct mp_append_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_append_impl<L<T...>>
{
    using type = L<T...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2, class... Lr> struct mp_append_impl<L1<T1...>, L2<T2...>, Lr...>
{
    using type = typename mp_append_impl<L1<T1..., T2...>, Lr...>::type;
};

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )
#else

template<
    template<class...> class L1, class... T1,
    template<class...> class L2, class... T2,
    template<class...> class L3, class... T3,
    template<class...> class L4, class... T4,
    template<class...> class L5, class... T5,
    template<class...> class L6, class... T6,
    template<class...> class L7, class... T7,
    template<class...> class L8, class... T8,
    template<class...> class L9, class... T9,
    template<class...> class L10, class... T10,
    class... Lr>
    struct mp_append_impl<L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>, L5<T5...>, L6<T6...>, L7<T7...>, L8<T8...>, L9<T9...>, L10<T10...>, Lr...>
{
    using type = typename mp_append_impl<L1<T1..., T2..., T3..., T4..., T5..., T6..., T7..., T8..., T9..., T10...>, Lr...>::type;
};

#endif

} // namespace detail

template<class... L> using mp_append = typename detail::mp_append_impl<L...>::type;

// mp_replace_front<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_front_impl;

template<template<class...> class L, class U1, class... U, class T> struct mp_replace_front_impl<L<U1, U...>, T>
{
    using type = L<T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_front = typename detail::mp_replace_front_impl<L, T>::type;

// mp_replace_first<L, T>
template<class L, class T> using mp_replace_first = typename detail::mp_replace_front_impl<L, T>::type;

// mp_replace_second<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_second_impl;

template<template<class...> class L, class U1, class U2, class... U, class T> struct mp_replace_second_impl<L<U1, U2, U...>, T>
{
    using type = L<U1, T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_second = typename detail::mp_replace_second_impl<L, T>::type;

// mp_replace_third<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_third_impl;

template<template<class...> class L, class U1, class U2, class U3, class... U, class T> struct mp_replace_third_impl<L<U1, U2, U3, U...>, T>
{
    using type = L<U1, U2, T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_third = typename detail::mp_replace_third_impl<L, T>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_LIST_HPP_INCLUDED
