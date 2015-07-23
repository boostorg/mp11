
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>
#include <tuple>

struct X1 {};
struct X2 {};
struct X3 {};
struct X4 {};
struct X5 {};
struct X6 {};
struct X7 {};
struct X8 {};
struct X9 {};

int main()
{
    using boost::mp_list;
    using boost::mp_reverse;

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1>>, mp_list<X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1, X2>>, mp_list<X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1, X2, X3>>, mp_list<X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1, X2, X3, X4>>, mp_list<X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1, X2, X3, X4, X5>>, mp_list<X5, X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1, X2, X3, X4, X5, X6>>, mp_list<X6, X5, X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1, X2, X3, X4, X5, X6, X7>>, mp_list<X7, X6, X5, X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1, X2, X3, X4, X5, X6, X7, X8>>, mp_list<X8, X7, X6, X5, X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<mp_list<X1, X2, X3, X4, X5, X6, X7, X8, X9>>, mp_list<X9, X8, X7, X6, X5, X4, X3, X2, X1>>));
    }

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<>>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1>>, std::tuple<X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1, X2>>, std::tuple<X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1, X2, X3>>, std::tuple<X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1, X2, X3, X4>>, std::tuple<X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1, X2, X3, X4, X5>>, std::tuple<X5, X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1, X2, X3, X4, X5, X6>>, std::tuple<X6, X5, X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1, X2, X3, X4, X5, X6, X7>>, std::tuple<X7, X6, X5, X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1, X2, X3, X4, X5, X6, X7, X8>>, std::tuple<X8, X7, X6, X5, X4, X3, X2, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::tuple<X1, X2, X3, X4, X5, X6, X7, X8, X9>>, std::tuple<X9, X8, X7, X6, X5, X4, X3, X2, X1>>));
    }

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_reverse<std::pair<X1, X2>>, std::pair<X2, X1>>));
    }

    return boost::report_errors();
}
