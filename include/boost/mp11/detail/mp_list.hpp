#ifndef BOOST_MP11_DETAIL_MP_LIST_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_LIST_HPP_INCLUDED

//  Copyright 2015, 2016 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/config.hpp>
#include <boost/mp11/detail/modules.hpp>

namespace boost
{
namespace mp11
{

// mp_list<T...>
BOOST_MODULE_EXPORT
template<class... T> struct mp_list
{
};

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_LIST_HPP_INCLUDED
