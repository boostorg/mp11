
//  Copyright 2015, 2017 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>
#include <tuple>
#include <utility>

struct X1 {};
struct X2 {};
struct X3 {};
struct X4 {};

using boost::mp11::mp_not;

template<class T> using add_pointer = T*;
template<class T> using is_not_ref = mp_not<std::is_reference<T>>;

int main()
{
    using boost::mp11::mp_list;
    using boost::mp11::mp_transform_if;

    using L1 = mp_list<X1, X2&, X3 const, X4 const&>;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_transform_if<is_not_ref, add_pointer, L1>, mp_list<X1*, X2&, X3 const*, X4 const&>>));

    using L2 = std::tuple<X1, X2&, X3 const, X4 const&>;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_transform_if<is_not_ref, add_pointer, L2>, std::tuple<X1*, X2&, X3 const*, X4 const&>>));

    using L3 = std::pair<X1 const, X2&>;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_transform_if<is_not_ref, add_pointer, L3>, std::pair<X1 const*, X2&>>));

    //

    return boost::report_errors();
}
