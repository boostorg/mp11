#ifndef BOOST_MP11_UTILITY_HPP_INCLUDED
#define BOOST_MP11_UTILITY_HPP_INCLUDED

//  Copyright 2015, 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>

namespace boost
{

// mp_identity
template<class T> struct mp_identity
{
    using type = T;
};

// mp_identity_t
template<class T> using mp_identity_t = T;

// mp_inherit
template<class... T> struct mp_inherit: T... {};

// mp_if, mp_if_c
namespace detail
{

template<bool C, class T, class E> struct mp_if_c_impl;

template<class T, class E> struct mp_if_c_impl<true, T, E>
{
    using type = T;
};

template<class T, class E> struct mp_if_c_impl<false, T, E>
{
    using type = E;
};

} // namespace detail

template<bool C, class T, class E> using mp_if_c = typename detail::mp_if_c_impl<C, T, E>::type;
template<class C, class T, class E> using mp_if = typename detail::mp_if_c_impl<static_cast<bool>(C::value), T, E>::type;

// mp_eval_if, mp_eval_if_c
namespace detail
{

template<bool C, class T, template<class...> class F, class... U> struct mp_eval_if_c_impl;

template<class T, template<class...> class F, class... U> struct mp_eval_if_c_impl<true, T, F, U...>
{
    using type = T;
};

template<class T, template<class...> class F, class... U> struct mp_eval_if_c_impl<false, T, F, U...>
{
    using type = F<U...>;
};

} // namespace detail

template<bool C, class T, template<class...> class F, class... U> using mp_eval_if_c = typename detail::mp_eval_if_c_impl<C, T, F, U...>::type;
template<class C, class T, template<class...> class F, class... U> using mp_eval_if = typename detail::mp_eval_if_c_impl<static_cast<bool>(C::value), T, F, U...>::type;

// mp_valid
// implementation by Bruno Dutra (by the name is_evaluable)
namespace detail
{

template<template<class...> class F, class... T> struct mp_valid_impl
{
    template<template<class...> class G, class = G<T...>> static mp_true check(int);
    template<template<class...> class> static mp_false check(...);

    using type = decltype(check<F>(0));
};

} // namespace detail

template<template<class...> class F, class... T> using mp_valid = typename detail::mp_valid_impl<F, T...>::type;

// mp_defer
namespace detail
{

template<template<class...> class F, class... T> struct mp_defer_impl
{
    using type = F<T...>;
};

struct mp_no_type
{
};

} // namespace detail

template<template<class...> class F, class... T> using mp_defer = mp_if<mp_valid<F, T...>, detail::mp_defer_impl<F, T...>, detail::mp_no_type>;

// mp_quote
template<template<class...> class F, class... T> struct mp_quote
{
    template<class... U> using apply = F<T..., U...>;
};

// mp_unquote
namespace detail
{

template<class Q, class... T> struct mp_unquote_impl
{
    using type = typename Q::template apply<T...>;
};

template<template<class...> class F, class... T, class... U> struct mp_unquote_impl<mp_quote<F, T...>, U...>
{
    using type = F<T..., U...>;
};

} // namespace detail

template<class Q, class... T> using mp_unquote = typename detail::mp_unquote_impl<Q, T...>::type;

} // namespace boost

#endif // #ifndef BOOST_MP11_UTILITY_HPP_INCLUDED
