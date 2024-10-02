#ifndef BOOST_MP11_LAMBDA_HPP_INCLUDED
#define BOOST_MP11_LAMBDA_HPP_INCLUDED

//  Copyright 2024 Joaquin M Lopez Munoz.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/bind.hpp>
#include <cstddef>
#include <type_traits>

#if defined(_MSC_VER) || defined(__GNUC__)
# pragma push_macro( "I" )
# undef I
#endif

namespace boost
{
namespace mp11
{
namespace detail
{

template<class T> struct lambda_impl;

} // namespace detail

// mp_lambda
template<class T> using mp_lambda = typename detail::lambda_impl<T>::type;

namespace detail
{

// base case (no placeholder replacement)
template<class T> struct lambda_impl
{
    template<class... U> using make = T;
    using type = mp_bind<make>;
};

// placeholders (behave directly as mp_bind expressions)
template<std::size_t I> struct lambda_impl<mp_arg<I>>
{
    using type = mp_arg<I>;
};

#define BOOST_MP11_SPECIALIZE_LAMBDA_IMPL(name, compound_type) \
template<class T> using lambda_make_##name = compound_type;    \
                                                               \
template<class T> struct lambda_impl<compound_type>            \
{                                                              \
    using type = mp_bind<lambda_make_##name, mp_lambda<T>>;    \
};

// [basic.type.qualifier]
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL(const, const T)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL(volatile, volatile T)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL(const_volatile, const volatile T)

// [dcl.ptr]
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL(pointer, T*)

// [dcl.ref]
// GCC < 7 fails with template<class U> using make = U&;
template<class T> struct lambda_impl<T&>
{
  template<class U> using make = typename std::add_lvalue_reference<U>::type;
  using type = mp_bind<make, mp_lambda<T>>;
};

template<class T> struct lambda_impl<T&&>
{
  template<class U> using make = typename std::add_rvalue_reference<U>::type;
  using type = mp_bind<make, mp_lambda<T>>;
};

// [dcl.array]
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL(array, T[])

#undef BOOST_MP11_SPECIALIZE_LAMBDA_IMPL

template<class T, std::size_t N> struct lambda_impl<T[N]>
{
    template<class Q> using make = Q[N];
    using type = mp_bind<make, mp_lambda<T>>;
};

// [dcl.fct], [dcl.mptr] (member functions)
template<template <class...> class F, class... T> struct lambda_devoid_args_impl
{
    using type = F<T...>;
};

template<template <class...> class F, class R> struct lambda_devoid_args_impl<F, R, void>
{
    using type = F<R>;
};

template<template <class...> class F, class R, class C> struct lambda_devoid_args_impl<F, R, C, void>
{
    using type = F<R,C>;
};

template<template <class...> class F> struct lambda_devoid_args
{
  template<class... T> using fn = typename lambda_devoid_args_impl<F, T...>::type;
};

#define BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(qualifier)                            \
template<class R, class... T> struct lambda_impl<R(T...) qualifier>                      \
{                                                                                        \
    template<class Q, class... U> using make = Q(U...) qualifier;                        \
    using type = mp_bind_q<lambda_devoid_args<make>, mp_lambda<R>, mp_lambda<T>...>;     \
};                                                                                       \
                                                                                         \
template<class R, class... T> struct lambda_impl<R(T..., ...) qualifier>                 \
{                                                                                        \
    template<class Q, class... U> using make = Q(U..., ...) qualifier;                   \
    using type = mp_bind_q<lambda_devoid_args<make>, mp_lambda<R>, mp_lambda<T>...>;     \
};                                                                                       \
                                                                                         \
template<class R, class C, class... T> struct lambda_impl<R (C::*)(T...) qualifier>      \
{                                                                                        \
    template<class Q, class D, class... U> using make = Q (D::*)(U...) qualifier;        \
    using type = mp_bind_q<                                                              \
        lambda_devoid_args<make>, mp_lambda<R>, mp_lambda<C>, mp_lambda<T>...>;          \
};                                                                                       \
                                                                                         \
template<class R, class C, class... T> struct lambda_impl<R (C::*)(T..., ...) qualifier> \
{                                                                                        \
    template<class Q, class D, class... U> using make = Q (D::*)(U..., ...) qualifier;   \
    using type = mp_bind_q<                                                              \
        lambda_devoid_args<make>, mp_lambda<R>, mp_lambda<C>, mp_lambda<T>...>;          \
};

#define BOOST_MP11_EMPTY()

BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(BOOST_MP11_EMPTY())
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(volatile)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const volatile)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(&)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const&)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(volatile&)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const volatile&)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(&&)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const&&)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(volatile&&)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const volatile&&)

#if (defined(_MSVC_LANG) &&  _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
// P0012R1: exception specification as part of the type system
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(volatile noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const volatile noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(& noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const& noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(volatile& noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const volatile& noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(&& noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const&& noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(volatile&& noexcept)
BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION(const volatile&& noexcept)
#endif // P0012R1

#undef BOOST_MP11_EMPTY
#undef BOOST_MP11_SPECIALIZE_LAMBDA_IMPL_FUNCTION

// [dcl.mptr] (data members)
template<class T, class C> struct lambda_impl<T (C::*)>
{
    template<class U, class D> using make = U (D::*);
    using type = mp_bind<make, mp_lambda<T>, mp_lambda<C>>;
};

// template class instantiation
template<template <class...> class C, class... Ts> struct lambda_impl<C<Ts...>>
{
    using type = mp_bind<C, mp_lambda<Ts>...>;
};

} // namespace detail
} // namespace mp11
} // namespace boost

#if defined(_MSC_VER) || defined(__GNUC__)
# pragma pop_macro( "I" )
#endif

#endif // #ifndef BOOST_MP11_LAMBDA_HPP_INCLUDED
