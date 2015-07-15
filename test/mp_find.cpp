
//  Copyright 2015 Peter Dimov.
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

int main()
{
    using boost::mp_list;
    using boost::mp_find;

    {
        using L1 = mp_list<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L1, void>, L1>));

        using L2 = mp_list<X1, X2, X2, X3, X3, X3>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L2, void>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L2, X1>, L2>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L2, X2>, mp_list<X2, X2, X3, X3, X3>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L2, X3>, mp_list<X3, X3, X3>>));
    }

    {
        using L3 = std::tuple<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L3, void>, L3>));

        using L4 = std::tuple<X1, X2, X2, X3, X3, X3>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L4, void>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L4, X1>, L4>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L4, X2>, std::tuple<X2, X2, X3, X3, X3>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find<L4, X3>, std::tuple<X3, X3, X3>>));
    }

    return boost::report_errors();
}
