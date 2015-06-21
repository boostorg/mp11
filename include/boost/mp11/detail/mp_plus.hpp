#ifndef BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <type_traits>

namespace boost
{

// mp_plus
namespace detail
{

template<class... T> struct mp_plus_impl;

#if defined( BOOST_NO_CXX11_CONSTEXPR )

template<> struct mp_plus_impl<>
{
	using type = std::integral_constant<int, 0>;
};

template<class T1, class... T> struct mp_plus_impl<T1, T...>
{
	static const/*expr*/ auto _v = T1::value + mp_plus<T...>::value;
	using type = std::integral_constant< typename std::remove_const<decltype(_v)>::type, _v >;
};

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T> struct mp_plus_impl<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>
{
	static const/*expr*/ auto _v = T1::value + T2::value + T3::value + T4::value + T5::value + T6::value + T7::value + T8::value + T9::value + T10::value + mp_plus<T...>::value;
	using type = std::integral_constant< typename std::remove_const<decltype(_v)>::type, _v >;
};

#else

constexpr int cx_plus()
{
	return 0;
}

template<class T1, class... T> constexpr auto cx_plus( T1 t1, T... t ) -> decltype( t1 + cx_plus( t... ) )
{
	return t1 + cx_plus( t... );
}

template<class... T> struct mp_plus_impl
{
	static constexpr auto _v = cx_plus( T::value... );
	using type = std::integral_constant< typename std::remove_const<decltype(_v)>::type, _v >;
};

#endif

} // namespace detail

template<class... T> using mp_plus = typename detail::mp_plus_impl<T...>::type;

} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED
