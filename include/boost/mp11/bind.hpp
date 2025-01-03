#ifndef BOOST_MP11_BIND_HPP_INCLUDED
#define BOOST_MP11_BIND_HPP_INCLUDED

//  Copyright 2017, 2018 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/config.hpp>
#ifndef BOOST_USE_MODULES
#include <cstddef>
#endif

#if defined(_MSC_VER) || defined(__GNUC__)
# pragma push_macro( "I" )
# undef I
#endif

namespace boost
{
namespace mp11
{

// mp_bind_front
BOOST_MP11_MODULE_EXPORT template<template<class...> class F, class... T> struct mp_bind_front
{
    // the indirection through mp_defer works around the language inability
    // to expand U... into a fixed parameter list of an alias template

    template<class... U> using fn = typename mp_defer<F, T..., U...>::type;
};

BOOST_MP11_MODULE_EXPORT template<class Q, class... T> using mp_bind_front_q = mp_bind_front<Q::template fn, T...>;

// mp_bind_back
BOOST_MP11_MODULE_EXPORT template<template<class...> class F, class... T> struct mp_bind_back
{
    template<class... U> using fn = typename mp_defer<F, U..., T...>::type;
};

BOOST_MP11_MODULE_EXPORT template<class Q, class... T> using mp_bind_back_q = mp_bind_back<Q::template fn, T...>;

// mp_arg
BOOST_MP11_MODULE_EXPORT template<std::size_t I> struct mp_arg
{
    template<class... T> using fn = mp_at_c<mp_list<T...>, I>;
};

BOOST_MP11_MODULE_EXPORT using _1 = mp_arg<0>;
BOOST_MP11_MODULE_EXPORT using _2 = mp_arg<1>;
BOOST_MP11_MODULE_EXPORT using _3 = mp_arg<2>;
BOOST_MP11_MODULE_EXPORT using _4 = mp_arg<3>;
BOOST_MP11_MODULE_EXPORT using _5 = mp_arg<4>;
BOOST_MP11_MODULE_EXPORT using _6 = mp_arg<5>;
BOOST_MP11_MODULE_EXPORT using _7 = mp_arg<6>;
BOOST_MP11_MODULE_EXPORT using _8 = mp_arg<7>;
BOOST_MP11_MODULE_EXPORT using _9 = mp_arg<8>;

// mp_bind
BOOST_MP11_MODULE_EXPORT template<template<class...> class F, class... T> struct mp_bind;

namespace detail
{

template<class V, class... T> struct eval_bound_arg
{
    using type = V;
};

template<std::size_t I, class... T> struct eval_bound_arg<mp_arg<I>, T...>
{
    using type = typename mp_arg<I>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind<F, U...>, T...>
{
    using type = typename mp_bind<F, U...>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind_front<F, U...>, T...>
{
    using type = typename mp_bind_front<F, U...>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind_back<F, U...>, T...>
{
    using type = typename mp_bind_back<F, U...>::template fn<T...>;
};

} // namespace detail

BOOST_MP11_MODULE_EXPORT template<template<class...> class F, class... T> struct mp_bind
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, == 1915 )
private:

    template<class... U> struct _f { using type = F<typename detail::eval_bound_arg<T, U...>::type...>; };

public:

    template<class... U> using fn = typename _f<U...>::type;

#else

    template<class... U> using fn = F<typename detail::eval_bound_arg<T, U...>::type...>;

#endif
};

BOOST_MP11_MODULE_EXPORT template<class Q, class... T> using mp_bind_q = mp_bind<Q::template fn, T...>;

} // namespace mp11
} // namespace boost

#if defined(_MSC_VER) || defined(__GNUC__)
# pragma pop_macro( "I" )
#endif

#endif // #ifndef BOOST_MP11_BIND_HPP_INCLUDED
