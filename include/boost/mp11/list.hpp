#ifndef BOOST_MP11_LIST_HPP_INCLUDED
#define BOOST_MP11_LIST_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_list.hpp>

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
