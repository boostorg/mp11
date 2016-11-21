#ifndef BOOST_MP11_ALGORITHM_HPP_INCLUDED
#define BOOST_MP11_ALGORITHM_HPP_INCLUDED

//  Copyright 2015, 2016 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/list.hpp>
#include <boost/mp11/set.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/mp11/detail/mp_plus.hpp>
#include <boost/mp11/detail/mp_map_find.hpp>
#include <boost/mp11/detail/config.hpp>
#include <boost/integer_sequence.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <type_traits>

namespace boost
{

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
#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1900 )

    template<class...> struct _f { using type = V; };
    using type = L<typename _f<T>::type...>;

#else

    template<class...> using _f = V;
    using type = L<_f<T>...>;

#endif
};

} // namespace detail

template<class L, class V> using mp_fill = typename detail::mp_fill_impl<L, V>::type;

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

// mp_product<F, L...>
namespace detail
{

template<template<class...> class F, class P, class... L> struct mp_product_impl_2;

template<template<class...> class F, class P> struct mp_product_impl_2<F, P>
{
    using type = mp_list<mp_rename<P, F>>;
};

template<template<class...> class F, class P, template<class...> class L1, class... T1, class... L> struct mp_product_impl_2<F, P, L1<T1...>, L...>
{
    using type = mp_append<typename mp_product_impl_2<F, mp_push_back<P, T1>, L...>::type...>;
};

template<template<class...> class F, class... L> struct mp_product_impl;

template<template<class...> class F, class L1, class... L> struct mp_product_impl<F, L1, L...>
{
    using type = mp_assign<L1, typename mp_product_impl_2<F, mp_list<>, L1, L...>::type>;
};

} // namespace detail

template<template<class...> class F, class... L> using mp_product = typename detail::mp_product_impl<F, L...>::type;

// mp_drop(_c)<L, N>
namespace detail
{

template<class L, class L2> struct mp_drop_impl;

template<template<class...> class L, class... T, template<class...> class L2, class... U> struct mp_drop_impl<L<T...>, L2<U...>>
{
    template<class... W> static mp_identity<L<W...>> f( U*..., mp_identity<W>*... );

    using R = decltype( f( (mp_identity<T>*)0 ... ) );

    using type = typename R::type;
};

} // namespace detail

template<class L, std::size_t N> using mp_drop_c = typename detail::mp_drop_impl<L, mp_repeat_c<mp_list<void>, N>>::type;

template<class L, class N> using mp_drop = typename detail::mp_drop_impl<L, mp_repeat<mp_list<void>, N>>::type;

// mp_iota(_c)<N>
namespace detail
{

template<class S> struct mp_from_sequence_impl;

template<template<class T, T... I> class S, class U, U... J> struct mp_from_sequence_impl<S<U, J...>>
{
    using type = mp_list<std::integral_constant<U, J>...>;
};

template<class S> using mp_from_sequence = typename mp_from_sequence_impl<S>::type;

} // namespace detail

template<std::size_t N> using mp_iota_c = detail::mp_from_sequence<make_index_sequence<N>>;
template<class N> using mp_iota = detail::mp_from_sequence<make_integer_sequence<typename std::remove_const<decltype(N::value)>::type, N::value>>;

// mp_at(_c)<L, I>
namespace detail
{

template<class L, class I> struct mp_at_impl
{
    static_assert( I::value >= 0, "mp_at<L, I>: I must not be negative" );

    using _map = mp_transform<mp_list, mp_iota<mp_size<L>>, L>;

    using type = mp_second<mp_map_find<_map, mp_size_t<I::value>>>;
};

} // namespace detail

template<class L, std::size_t I> using mp_at_c = typename detail::mp_at_impl<L, mp_size_t<I>>::type;

template<class L, class I> using mp_at = typename detail::mp_at_impl<L, I>::type;

// mp_take(_c)<L, N>
namespace detail
{

template<class L, class N> struct mp_take_impl
{
    static_assert( N::value >= 0, "mp_take<L, N>: N must not be negative" );

    using _map = mp_transform<mp_list, mp_iota<mp_size<L>>, L>;

    template<class I> using _f = mp_second<mp_map_find<_map, I>>;

    using _ind = mp_iota_c<N::value>;

    using type = mp_assign<L, mp_transform<_f, _ind>>;
};

} // namespace detail

template<class L, std::size_t N> using mp_take_c = typename detail::mp_take_impl<L, mp_size_t<N>>::type;

template<class L, class N> using mp_take = typename detail::mp_take_impl<L, N>::type;

// mp_replace<L, V, W>
namespace detail
{

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<class L, class V, class W> struct mp_replace_impl;

template<template<class...> class L, class... T, class V, class W> struct mp_replace_impl<L<T...>, V, W>
{
    template<class A> struct _f { using type = mp_if<std::is_same<A, V>, W, A>; };

    using type = L<typename _f<T>::type...>;
};

#else

template<class L, class V, class W> struct mp_replace_impl
{
    template<class A> using _f = mp_if<std::is_same<A, V>, W, A>;

    using type = mp_transform<_f, L>;
};

#endif

} // namespace detail

template<class L, class V, class W> using mp_replace = typename detail::mp_replace_impl<L, V, W>::type;

// mp_replace_if<L, P, W>
namespace detail
{

template<class L, template<class...> class P, class W> struct mp_replace_if_impl
{
    template<class T> using _f = mp_if<P<T>, W, T>;

    using type = mp_transform<_f, L>;
};

} // namespace detail

template<class L, template<class...> class P, class W> using mp_replace_if = typename detail::mp_replace_if_impl<L, P, W>::type;

// mp_copy_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_copy_if_impl;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_copy_if_impl<L<T...>, P>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<>;
};

#else

template<template<class...> class L, template<class...> class P> struct mp_copy_if_impl<L<>, P>
{
    using type = L<>;
};

#endif

template<template<class...> class L, class T1, class... T, template<class...> class P> struct mp_copy_if_impl<L<T1, T...>, P>
{
    using rest = typename mp_copy_if_impl<L<T...>, P>::type;
    using type = mp_if<P<T1>, mp_push_front<rest, T1>, rest>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_copy_if = typename detail::mp_copy_if_impl<L, P>::type;

// mp_remove<L, V>
namespace detail
{

template<class L, class V> struct mp_remove_impl;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, class V> struct mp_remove_impl<L<T...>, V>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<>;
};

#else

template<template<class...> class L, class V> struct mp_remove_impl<L<>, V>
{
    using type = L<>;
};

#endif

template<template<class...> class L, class T1, class... T> struct mp_remove_impl<L<T1, T...>, T1>
{
    using type = typename mp_remove_impl<L<T...>, T1>::type;
};

template<template<class...> class L, class T1, class... T, class V> struct mp_remove_impl<L<T1, T...>, V>
{
    using rest = typename mp_remove_impl<L<T...>, V>::type;
    using type = mp_push_front<rest, T1>;
};

} // namespace detail

template<class L, class V> using mp_remove = typename detail::mp_remove_impl<L, V>::type;

// mp_remove_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_remove_if_impl;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_remove_if_impl<L<T...>, P>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<>;
};

#else

template<template<class...> class L, template<class...> class P> struct mp_remove_if_impl<L<>, P>
{
    using type = L<>;
};

#endif

template<template<class...> class L, class T1, class... T, template<class...> class P> struct mp_remove_if_impl<L<T1, T...>, P>
{
    using rest = typename mp_remove_if_impl<L<T...>, P>::type;
    using type = mp_if<P<T1>, rest, mp_push_front<rest, T1>>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_remove_if = typename detail::mp_remove_if_impl<L, P>::type;

// mp_partition<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_partition_impl;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_partition_impl<L<T...>, P>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<L<>, L<>>;
};

#else

template<template<class...> class L, template<class...> class P> struct mp_partition_impl<L<>, P>
{
    using type = L<L<>, L<>>;
};

#endif

template<template<class...> class L, class T1, class... T, template<class...> class P> struct mp_partition_impl<L<T1, T...>, P>
{
    using rest = typename mp_partition_impl<L<T...>, P>::type;
    using type = mp_if<P<T1>, L<mp_push_front<mp_first<rest>, T1>, mp_second<rest>>, L<mp_first<rest>, mp_push_front<mp_second<rest>, T1>>>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_partition = typename detail::mp_partition_impl<L, P>::type;

// mp_sort<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_sort_impl;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_sort_impl<L<T...>, P>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<>;
};

#else

template<template<class...> class L, template<class...> class P> struct mp_sort_impl<L<>, P>
{
    using type = L<>;
};

#endif

template<template<class...> class L, class T1, template<class...> class P> struct mp_sort_impl<L<T1>, P>
{
    using type = L<T1>;
};

template<template<class...> class L, class T1, class... T, template<class...> class P> struct mp_sort_impl<L<T1, T...>, P>
{
    template<class U> using F = P<U, T1>;

    using part = mp_partition<L<T...>, F>;

    using S1 = typename mp_sort_impl<mp_first<part>, P>::type;
    using S2 = typename mp_sort_impl<mp_second<part>, P>::type;

    using type = mp_append<mp_push_back<S1, T1>, S2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_sort = typename detail::mp_sort_impl<L, P>::type;

// mp_find_index<L, V>
namespace detail
{

template<class L, class V> struct mp_find_index_impl;

#if !defined( BOOST_MP11_NO_CONSTEXPR )

template<template<class...> class L, class V> struct mp_find_index_impl<L<>, V>
{
    using type = mp_size_t<0>;
};

constexpr std::size_t cx_find_index( bool const * first, bool const * last )
{
    return first == last || *first? 0: 1 + cx_find_index( first + 1, last );
}

template<template<class...> class L, class... T, class V> struct mp_find_index_impl<L<T...>, V>
{
    static constexpr bool _v[] = { std::is_same<T, V>::value... };
    using type = mp_size_t< cx_find_index( _v, _v + sizeof...(T) ) >;
};

#else

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, class V> struct mp_find_index_impl<L<T...>, V>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = mp_size_t<0>;
};

#else

template<template<class...> class L, class V> struct mp_find_index_impl<L<>, V>
{
    using type = mp_size_t<0>;
};

#endif

template<template<class...> class L, class... T, class V> struct mp_find_index_impl<L<V, T...>, V>
{
    using type = mp_size_t<0>;
};

template<template<class...> class L, class T1, class... T, class V> struct mp_find_index_impl<L<T1, T...>, V>
{
    using _r = typename mp_find_index_impl<mp_list<T...>, V>::type;
    using type = mp_size_t<1 + _r::value>;
};

#endif

} // namespace detail

template<class L, class V> using mp_find_index = typename detail::mp_find_index_impl<L, V>::type;

// mp_find_index_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_find_index_if_impl;

#if !defined( BOOST_MP11_NO_CONSTEXPR )

template<template<class...> class L, template<class...> class P> struct mp_find_index_if_impl<L<>, P>
{
    using type = mp_size_t<0>;
};

template<template<class...> class L, class... T, template<class...> class P> struct mp_find_index_if_impl<L<T...>, P>
{
    static constexpr bool _v[] = { P<T>::value... };
    using type = mp_size_t< cx_find_index( _v, _v + sizeof...(T) ) >;
};

#else

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_find_index_if_impl<L<T...>, P>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = mp_size_t<0>;
};

#else

template<template<class...> class L, template<class...> class P> struct mp_find_index_if_impl<L<>, P>
{
    using type = mp_size_t<0>;
};

#endif

template<class L, template<class...> class P> struct mp_find_index_if_impl_2
{
    using _r = typename mp_find_index_if_impl<L, P>::type;
    using type = mp_size_t<1 + _r::value>;
};

template<template<class...> class L, class T1, class... T, template<class...> class P> struct mp_find_index_if_impl<L<T1, T...>, P>
{
    using type = typename mp_if<P<T1>, mp_identity<mp_size_t<0>>, mp_find_index_if_impl_2<mp_list<T...>, P>>::type;
};

#endif

} // namespace detail

template<class L, template<class...> class P> using mp_find_index_if = typename detail::mp_find_index_if_impl<L, P>::type;

// mp_find<L, V>
template<class L, class V> using mp_find = mp_drop<L, mp_find_index<L, V>>;

// mp_find_if<L, P>
template<class L, template<class...> class P> using mp_find_if = mp_drop<L, mp_find_index_if<L, P>>;

// mp_reverse<L>
namespace detail
{

template<class L> struct mp_reverse_impl;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T> struct mp_reverse_impl<L<T...>>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<>;
};

#else

template<template<class...> class L> struct mp_reverse_impl<L<>>
{
    using type = L<>;
};

#endif

template<template<class...> class L, class T1> struct mp_reverse_impl<L<T1>>
{
    using type = L<T1>;
};

template<template<class...> class L, class T1, class T2> struct mp_reverse_impl<L<T1, T2>>
{
    using type = L<T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3> struct mp_reverse_impl<L<T1, T2, T3>>
{
    using type = L<T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4> struct mp_reverse_impl<L<T1, T2, T3, T4>>
{
    using type = L<T4, T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5> struct mp_reverse_impl<L<T1, T2, T3, T4, T5>>
{
    using type = L<T5, T4, T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class... T> struct mp_reverse_impl<L<T1, T2, T3, T4, T5, T6, T...>>
{
    using type = mp_push_back<typename mp_reverse_impl<L<T...>>::type, T6, T5, T4, T3, T2, T1>;
};

} // namespace detail

template<class L> using mp_reverse = typename detail::mp_reverse_impl<L>::type;

// mp_fold<L, V, F>
namespace detail
{

template<class L, class V, template<class...> class F> struct mp_fold_impl;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, class V, template<class...> class F> struct mp_fold_impl<L<T...>, V, F>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = V;
};

#else

template<template<class...> class L, class V, template<class...> class F> struct mp_fold_impl<L<>, V, F>
{
    using type = V;
};

#endif

template<template<class...> class L, class T1, class... T, class V, template<class...> class F> struct mp_fold_impl<L<T1, T...>, V, F>
{
    using type = typename mp_fold_impl<L<T...>, F<V, T1>, F>::type;
};

} // namespace detail

template<class L, class V, template<class...> class F> using mp_fold = typename detail::mp_fold_impl<L, V, F>::type;

// mp_reverse_fold<L, V, F>
namespace detail
{

template<class L, class V, template<class...> class F> struct mp_reverse_fold_impl;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )

template<template<class...> class L, class... T, class V, template<class...> class F> struct mp_reverse_fold_impl<L<T...>, V, F>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = V;
};

#else

template<template<class...> class L, class V, template<class...> class F> struct mp_reverse_fold_impl<L<>, V, F>
{
    using type = V;
};

#endif

template<template<class...> class L, class T1, class... T, class V, template<class...> class F> struct mp_reverse_fold_impl<L<T1, T...>, V, F>
{
    using rest = typename mp_reverse_fold_impl<L<T...>, V, F>::type;
    using type = F<T1, rest>;
};

} // namespace detail

template<class L, class V, template<class...> class F> using mp_reverse_fold = typename detail::mp_reverse_fold_impl<L, V, F>::type;

// mp_unique<L>
namespace detail
{

template<class L> struct mp_unique_impl;

template<template<class...> class L, class... T> struct mp_unique_impl<L<T...>>
{
    using type = mp_set_push_back<L<>, T...>;
};

} // namespace detail

template<class L> using mp_unique = typename detail::mp_unique_impl<L>::type;

// mp_all_of<L, P>
template<class L, template<class...> class P> using mp_all_of = mp_bool< mp_count_if<L, P>::value == mp_size<L>::value >;

// mp_none_of<L, P>
template<class L, template<class...> class P> using mp_none_of = mp_bool< mp_count_if<L, P>::value == 0 >;

// mp_any_of<L, P>
template<class L, template<class...> class P> using mp_any_of = mp_bool< mp_count_if<L, P>::value != 0 >;

} // namespace boost

#endif // #ifndef BOOST_MP11_ALGORITHM_HPP_INCLUDED
