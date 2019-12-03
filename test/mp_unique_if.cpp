//  Copyright 2015 Peter Dimov.
//  Copyright 2019 Kris Jusiak.
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

int main()
{
    using boost::mp11::mp_list;
    using boost::mp11::mp_unique_if;

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<>, std::is_same>,mp_list<>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void>, std::is_same>,mp_list<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void, void>, std::is_same>,mp_list<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void, void, void>, std::is_same>,mp_list<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void, void, void, void>, std::is_same>,mp_list<void>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void, int>, std::is_same>,mp_list<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void, void, void, int, int, int>, std::is_same>,mp_list<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void, int, void, int, int, void, int, int, int>, std::is_same>,mp_list<void, int>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void, int, char[]>, std::is_same>,mp_list<void, int, char[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<mp_list<void, int, char[], void, int, char[], void, int, char[]>, std::is_same>,mp_list<void, int, char[]>>));
    }

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<>, std::is_same>,std::tuple<>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void>, std::is_same>,std::tuple<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void, void>, std::is_same>,std::tuple<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void, void, void>, std::is_same>,std::tuple<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void, void, void, void>, std::is_same>,std::tuple<void>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void, int>, std::is_same>,std::tuple<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void, void, void, int, int, int>, std::is_same>,std::tuple<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void, int, void, int, int, void, int, int, int>, std::is_same>,std::tuple<void, int>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void, int, char[]>, std::is_same>,std::tuple<void, int, char[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if<std::tuple<void, int, char[], void, int, char[], void, int, char[]>, std::is_same>,std::tuple<void, int, char[]>>));
    }

    return boost::report_errors();
}
