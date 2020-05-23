#ifndef BOOST_MP11_TUPLE_HPP_INCLUDED
#define BOOST_MP11_TUPLE_HPP_INCLUDED

//  Copyright 2015, 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integer_sequence.hpp>
#include <boost/mp11/detail/config.hpp>
#include <tuple>
#include <utility>
#include <type_traits>
#include <cstddef>

#if BOOST_MP11_MSVC
# pragma warning( push )
# pragma warning( disable: 4100 ) // unreferenced formal parameter 'tp'
#endif

namespace boost
{
namespace mp11
{

// tuple_apply
namespace detail
{

template<class F, class Tp, std::size_t... J> BOOST_MP11_CONSTEXPR auto tuple_apply_impl( F && f, Tp && tp, integer_sequence<std::size_t, J...> )
    -> decltype( std::forward<F>(f)( std::get<J>(std::forward<Tp>(tp))... ) )
{
    return std::forward<F>(f)( std::get<J>(std::forward<Tp>(tp))... );
}

} // namespace detail

template<class F, class Tp,
    class Seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>>
BOOST_MP11_CONSTEXPR auto tuple_apply( F && f, Tp && tp )
    -> decltype( detail::tuple_apply_impl( std::forward<F>(f), std::forward<Tp>(tp), Seq() ) )
{
    return detail::tuple_apply_impl( std::forward<F>(f), std::forward<Tp>(tp), Seq() );
}

// construct_from_tuple
namespace detail
{

template<class T, class Tp, std::size_t... J> BOOST_MP11_CONSTEXPR T construct_from_tuple_impl( Tp && tp, integer_sequence<std::size_t, J...> )
{
    return T( std::get<J>(std::forward<Tp>(tp))... );
}

} // namespace detail

template<class T, class Tp,
    class Seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>>
BOOST_MP11_CONSTEXPR T construct_from_tuple( Tp && tp )
{
    return detail::construct_from_tuple_impl<T>( std::forward<Tp>(tp), Seq() );
}

// tuple_for_each
namespace detail
{

template<class Tp, std::size_t... J, class F> BOOST_MP11_CONSTEXPR F tuple_for_each_impl( Tp && tp, integer_sequence<std::size_t, J...>, F && f )
{
    using A = int[sizeof...(J)];
    return (void)A{ ((void)f(std::get<J>(std::forward<Tp>(tp))), 0)... }, std::forward<F>(f);
}

template<class Tp, class F> BOOST_MP11_CONSTEXPR F tuple_for_each_impl( Tp && /*tp*/, integer_sequence<std::size_t>, F && f )
{
    return std::forward<F>(f);
}

} // namespace detail

template<class Tp, class F> BOOST_MP11_CONSTEXPR F tuple_for_each( Tp && tp, F && f )
{
    using seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>;
    return detail::tuple_for_each_impl( std::forward<Tp>(tp), seq(), std::forward<F>(f) );
}

// tuple_transform
namespace detail
{

template <class Tp, class F, class... Tps>
struct tuple_transform_caller {
    F const& f_;
    std::tuple<Tp const&, Tps const&...> const tps_;

    BOOST_MP11_CONSTEXPR tuple_transform_caller( Tp const& tp, F const& f, Tps const&... tps )
        : f_{f}, tps_{tp, tps...} {}

    template <std::size_t J, std::size_t... I>
    BOOST_MP11_CONSTEXPR auto operator()(
        std::integral_constant<std::size_t, J>,
        integer_sequence<std::size_t, I...>) const
        -> decltype(f_(std::get<J>(std::get<I>(tps_))...))
    {
        return f_(std::get<J>(std::get<I>(tps_))...);
    }
};

template <class Tp, class F>
struct tuple_transform_caller<Tp, F> {
    F const& f_;
    Tp const& tp_;

    BOOST_MP11_CONSTEXPR tuple_transform_caller( Tp const& tp, F const& f )
        : f_{f}, tp_{tp} {}

    template <std::size_t J>
    BOOST_MP11_CONSTEXPR auto operator()(
        std::integral_constant<std::size_t, J>,
        integer_sequence<std::size_t, 0>
    ) const
        -> decltype(f_(std::get<J>(tp_)))
    {
        return f_(std::get<J>(tp_));
    }
};

template<
    template <class...> class Tp,
    class... Ts,
    class... Us,
    std::size_t... J,
    class Seq = make_index_sequence<sizeof...(Us)>, // tuple sequence
    class R = Tp<decltype(std::declval<tuple_transform_caller<Tp<Ts...>, Us...>>()(
        std::integral_constant<std::size_t, J>{}, Seq{}
    ))...>
>
BOOST_MP11_CONSTEXPR R tuple_transform_impl(
    tuple_transform_caller<Tp<Ts...>, Us...> c,
    integer_sequence<std::size_t, J...>)
{
    return R( c(std::integral_constant<std::size_t, J>{}, Seq{})... );
}

} // namespace detail

// warning: evaluation order is undefined
template<
  class F,
  class Tp,
  class... Tps,
  class Seq = make_index_sequence<std::tuple_size<Tp>::value> // element sequence
>
BOOST_MP11_CONSTEXPR auto tuple_transform( F const& f, Tp const& tp, Tps const&... tps )
  -> decltype(detail::tuple_transform_impl(
        std::declval<detail::tuple_transform_caller<Tp, F, Tps...>>(), Seq{}
    ))
{
    return detail::tuple_transform_impl(
        detail::tuple_transform_caller<Tp, F, Tps...>{ tp, f, tps... }, Seq{}
    );
}

} // namespace mp11
} // namespace boost

#if BOOST_MP11_MSVC
# pragma warning( pop )
#endif

#endif // #ifndef BOOST_TUPLE_HPP_INCLUDED
