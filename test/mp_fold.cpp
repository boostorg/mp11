
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

template<class T1, class T2> struct F {};

int main()
{
    using boost::mp11::mp_list;
    using boost::mp11::mp_fold;

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<mp_list<>, void, F>, void>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<mp_list<X1>, void, F>, F<void, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<mp_list<X1, X2>, void, F>, F<F<void, X1>, X2>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<mp_list<X1, X2, X3>, void, F>, F<F<F<void, X1>, X2>, X3>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<mp_list<X1, X2, X3, X4>, void, F>, F<F<F<F<void, X1>, X2>, X3>, X4>>));
    }

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<std::tuple<>, void, F>, void>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<std::tuple<X1>, void, F>, F<void, X1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<std::tuple<X1, X2>, void, F>, F<F<void, X1>, X2>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<std::tuple<X1, X2, X3>, void, F>, F<F<F<void, X1>, X2>, X3>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<std::tuple<X1, X2, X3, X4>, void, F>, F<F<F<F<void, X1>, X2>, X3>, X4>>));
    }

    using boost::mp11::mp_push_back;

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<std::tuple<X1, X2, X3, X4>, mp_list<>, mp_push_back>, mp_list<X1, X2, X3, X4>>));
    }

    using boost::mp11::mp_push_front;

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_fold<std::tuple<X1, X2, X3, X4>, mp_list<>, mp_push_front>, mp_list<X4, X3, X2, X1>>));
    }

    return boost::report_errors();
}
