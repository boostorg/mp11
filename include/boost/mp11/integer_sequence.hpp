#ifndef BOOST_MP11_INTEGER_SEQUENCE_HPP_INCLUDED
#define BOOST_MP11_INTEGER_SEQUENCE_HPP_INCLUDED

// Copyright 2015, 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/version.hpp>
#include <cstddef>

#if defined(_MSC_VER) || defined(__GNUC__)
# pragma push_macro( "I" )
# undef I
#endif

#if defined(__has_builtin)
# if __has_builtin(__make_integer_seq)
#  define BOOST_MP11_HAS_MAKE_INTEGER_SEQ
# elif __has_builtin(__integer_pack)
#  define BOOST_MP11_HAS_INTEGER_PACK
# endif
#endif

namespace boost
{
namespace mp11
{

// integer_sequence
template<class T, T... I> struct integer_sequence
{
};

#if defined(BOOST_MP11_HAS_MAKE_INTEGER_SEQ)

template<class T, T N> using make_integer_sequence = __make_integer_seq<integer_sequence, T, N>;

#elif defined(BOOST_MP11_HAS_INTEGER_PACK)

template<class T, T N> using make_integer_sequence = integer_sequence<T, __integer_pack(N)...>;

#else

// detail::make_integer_sequence_impl
namespace detail
{
template<bool, class T, T N, class L>
struct iseq_expand;

template<class T, T N, T... I>
struct iseq_expand<false, T, N, integer_sequence<T, I...>>
{
    using type = integer_sequence<T, I..., (N+I)...>;
};

template<class T, T N, T... I>
struct iseq_expand<true, T, N, integer_sequence<T, I...>>
{
    using type = integer_sequence<T, I..., (N+I)..., N * 2>;
};

template<class T, T N, T Zero, T One> struct make_integer_sequence_impl
{
    static_assert( N >= 0, "make_integer_sequence<T, N>: N must not be negative" );

    using type = typename iseq_expand<N & 1, T, N / 2, typename make_integer_sequence_impl<T, N / 2, Zero, One>::type>::type;
};

template<class T, T Zero, T One> struct make_integer_sequence_impl<T, Zero, Zero, One>
{
    using type = integer_sequence<T>;
};

template<class T, T Zero, T One> struct make_integer_sequence_impl<T, One, Zero, One>
{
    using type = integer_sequence<T, Zero>;
};

} // namespace detail

// make_integer_sequence
template<class T, T N> using make_integer_sequence = typename detail::make_integer_sequence_impl<T, N, 0, 1>::type;

#endif // defined(BOOST_MP11_HAS_MAKE_INTEGER_SEQ)

// index_sequence
template<std::size_t... I> using index_sequence = integer_sequence<std::size_t, I...>;

// make_index_sequence
template<std::size_t N> using make_index_sequence = make_integer_sequence<std::size_t, N>;

// index_sequence_for
template<class... T> using index_sequence_for = make_integer_sequence<std::size_t, sizeof...(T)>;

} // namespace mp11
} // namespace boost

#if defined(_MSC_VER) || defined(__GNUC__)
# pragma pop_macro( "I" )
#endif

#endif // #ifndef BOOST_MP11_INTEGER_SEQUENCE_HPP_INCLUDED
