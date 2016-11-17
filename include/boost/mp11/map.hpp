#ifndef BOOST_MP11_MAP_HPP_INCLUDED
#define BOOST_MP11_MAP_HPP_INCLUDED

//  Copyright 2015, 2016 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_map_find.hpp>
#include <boost/mp11/integral.hpp>
#include <type_traits>

namespace boost
{

// mp_map_contains<M, K>
template<class M, class K> using mp_map_contains = mp_not<std::is_same<mp_map_find<M, K>, void>>;

// mp_map_insert<M, T>
// mp_map_replace<M, T>
// mp_map_update<M, T, F>
// mp_map_erase<M, K>

} // namespace boost

#endif // #ifndef BOOST_MP11_MAP_HPP_INCLUDED
