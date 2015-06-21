#ifndef BOOST_MP11_LIST_HPP_INCLUDED
#define BOOST_MP11_LIST_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_plus.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <type_traits>

namespace boost
{

// mp_list<T...>
template<class... T> struct mp_list
{
};

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

// mp_assign<L1, L2>
namespace detail
{

template<class L1, class L2> struct mp_assign_impl;

template<template<class...> class L1, class... T, template<class...> class L2, class... U> struct mp_assign_impl<L1<T...>, L2<U...>>
{
    using type = L1<U...>;
};

} // namespace detail

template<class L1, class L2> using mp_assign = typename detail::mp_assign_impl<L1, L2>::type;

// mp_clear<L>
template<class L> using mp_clear = mp_assign<L, mp_list<>>;

// mp_transform<F, L...>
namespace detail
{

template<template<class...> class F, class... L> struct mp_transform_impl;

template<template<class...> class F, class... L> using mp_transform = typename mp_transform_impl<F, L...>::type;

template<template<class...> class F, template<class...> class L, class... T> struct mp_transform_impl<F, L<T...>>
{
    using type = L<F<T>...>;
};

template<template<class...> class F, template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_transform_impl<F, L1<T1...>, L2<T2...>>
{
    static_assert( sizeof...(T1) == sizeof...(T2), "The arguments of mp_transform should be of the same size" );
    using type = L1<F<T1,T2>...>;
};

template<template<class...> class F, template<class...> class L1, class... T1, template<class...> class L2, class... T2, template<class...> class L3, class... T3> struct mp_transform_impl<F, L1<T1...>, L2<T2...>, L3<T3...>>
{
    static_assert( sizeof...(T1) == sizeof...(T2) && sizeof...(T1) == sizeof...(T3), "The arguments of mp_transform should be of the same size" );
    using type = L1<F<T1,T2,T3>...>;
};

} // namespace detail

template<template<class...> class F, class... L> using mp_transform = typename detail::mp_transform_impl<F, L...>::type;

// mp_fill<L, V>
namespace detail
{

template<class L, class V> struct mp_fill_impl;

template<template<class...> class L, class... T, class V> struct mp_fill_impl<L<T...>, V>
{
#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

    template<class...> struct _f { using type = V; };
    using type = L<typename _f<T>::type...>;

#else

    template<class...> using _f = V;
    using type = L<_f<T>...>;

#endif
};

} // namespace detail

template<class L, class V> using mp_fill = typename detail::mp_fill_impl<L, V>::type;

// mp_count<L, V>
namespace detail
{

template<class L, class V> struct mp_count_impl;

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_plus<std::is_same<T, V>...>;
};

} // namespace detail

template<class L, class V> using mp_count = typename detail::mp_count_impl<L, V>::type;

// mp_count_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_count_if_impl;

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

    template<class T> struct _f { using type = mp_to_bool<P<T>>; };
    using type = mp_plus<typename _f<T>::type...>;

#else

    using type = mp_plus<mp_to_bool<P<T>>...>;

#endif
};

} // namespace detail

template<class L, template<class...> class P> using mp_count_if = typename detail::mp_count_if_impl<L, P>::type;

// mp_contains<L, V>
template<class L, class V> using mp_contains = mp_to_bool<mp_count<L, V>>;

// mp_repeat(_c)<L, N>
namespace detail
{

template<class L, std::size_t N> struct mp_repeat_c_impl
{
    using _l1 = typename mp_repeat_c_impl<L, N/2>::type;
    using _l2 = typename mp_repeat_c_impl<L, N%2>::type;

    using type = mp_append<_l1, _l1, _l2>;
};

template<class L> struct mp_repeat_c_impl<L, 0>
{
    using type = mp_clear<L>;
};

template<class L> struct mp_repeat_c_impl<L, 1>
{
    using type = L;
};

template<class L, class N> struct mp_repeat_impl
{
    static_assert( N::value >= 0, "mp_repeat<L, N>: N must not be negative" );

    using type = typename mp_repeat_c_impl<L, N::value>::type;
};

} // namespace detail

template<class L, std::size_t N> using mp_repeat_c = typename detail::mp_repeat_c_impl<L, N>::type;
template<class L, class N> using mp_repeat = typename detail::mp_repeat_impl<L, N>::type;

// mp_drop<L, N>
// mp_take<L, N>
// mp_find<L, V>
// mp_find_if<L, P>
// mp_find_index<L, V>
// mp_find_index_if<L, P>
// mp_reverse<L>
// mp_copy_if<L, P>
// mp_remove_if<L, P>
// mp_product<L...>?
// mp_fold<L, V, F>
// mp_reverse_fold<L, V, F>
// mp_replace<L, V1, V2>?
// mp_replace_if<L, P, V2>?
// mp_partition<L, P>
// mp_sort<L>

} // namespace boost

#endif // #ifndef BOOST_MP11_LIST_HPP_INCLUDED
