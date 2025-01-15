#ifndef BOOST_MP11_MPL_LIST_HPP_INCLUDED
#define BOOST_MP11_MPL_LIST_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#if defined(BOOST_USE_MODULES) && !defined(BOOST_MP11_INTERFACE_UNIT)

#include <boost/mp11/version.hpp>
import boost.mp11;

#else

#include <boost/mp11/detail/mpl_common.hpp>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<mp11::mp_list<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif

#endif // #ifndef BOOST_MP11_MPL_LIST_HPP_INCLUDED
