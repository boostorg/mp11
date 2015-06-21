#ifndef BOOST_MP11_UTILITY_HPP_INCLUDED
#define BOOST_MP11_UTILITY_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost
{

// mp_identity
template<class T> struct mp_identity
{
    using type = T;
};

// mp_inherit
template<class... T> struct mp_inherit: T... {};

// mp_if
template<bool C, class T, class E> struct mp_if_c_impl;

template<class T, class E> struct mp_if_c_impl<true, T, E>
{
    using type = T;
};

template<class T, class E> struct mp_if_c_impl<false, T, E>
{
    using type = E;
};

template<bool C, class T, class E> using mp_if_c = typename mp_if_c_impl<C, T, E>::type;

template<class C, class T, class E> using mp_if = typename mp_if_c_impl<static_cast<bool>( C::value ), T, E>::type;

// mp_eval_if
template<bool C, class T, template<class...> class F, class... U> struct mp_eval_if_c_impl;

template<class T, template<class...> class F, class... U> struct mp_eval_if_c_impl<true, T, F, U...>
{
    using type = T;
};

template<class T, template<class...> class F, class... U> struct mp_eval_if_c_impl<false, T, F, U...>
{
    using type = F<U...>;
};

template<bool C, class T, template<class...> class F, class... U> using mp_eval_if_c = typename mp_eval_if_c_impl<C, T, F, U...>::type;

template<class C, class T, template<class...> class F, class... U> using mp_eval_if = typename mp_eval_if_c_impl<static_cast<bool>( C::value ), T, F, U...>::type;

} // namespace boost

#endif // #ifndef BOOST_MP11_UTILITY_HPP_INCLUDED
