#ifndef BOOST_TUPLE_FOR_EACH_HPP_INCLUDED
#define BOOST_TUPLE_FOR_EACH_HPP_INCLUDED

#include <boost/integer_sequence.hpp>
#include <boost/config.hpp>
#include <tuple>
#include <utility>
#include <type_traits>
#include <cstddef>

namespace boost
{

namespace detail
{

template<class Tp, std::size_t... J, class F> BOOST_CONSTEXPR F tuple_for_each_impl( Tp && tp, boost::integer_sequence<std::size_t, J...>, F && f )
{
    using A = int[sizeof...(J)];
    return (void)A{ ((void)f(std::get<J>(std::forward<Tp>(tp))), 0)... }, std::forward<F>(f);
}

} // namespace detail

template<class Tp, class F> BOOST_CONSTEXPR F tuple_for_each( Tp && tp, F && f )
{
    using seq = boost::make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>;
    return detail::tuple_for_each_impl( std::forward<Tp>(tp), seq(), std::forward<F>(f) );
}

} // namespace boost

#endif // #ifndef BOOST_TUPLE_FOR_EACH_HPP_INCLUDED
