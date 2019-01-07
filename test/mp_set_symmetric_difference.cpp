
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/set.hpp>
#include <boost/mp11/list.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>
#include <tuple>

int main()
{
    using boost::mp11::mp_list;
    using boost::mp11::mp_set_symmetric_difference;

    {
        using L1 = mp_list<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1,  L1>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, mp_list<void>>, mp_list<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, mp_list<int>>, mp_list<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, mp_list<void, int>>, mp_list<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, mp_list<void, int, char[]>>, mp_list<void, int, char[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, mp_list<void, int, void, int, void, int>>, mp_list<void, int>>));
    }

    {
        using L2 = mp_list<void>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2>, L2>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, mp_list<>>, L2>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, mp_list<void>>, mp_list<void>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, mp_list<int>>, mp_list<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, mp_list<void, int>>, mp_list<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, mp_list<void, void, void, int, int, int>>, mp_list<void, int>>));
    }

    {
        using L3 = mp_list<void, int>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3>, L3>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, mp_list<>>, L3>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, mp_list<void>>, mp_list<int, void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, mp_list<int>>, mp_list<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, mp_list<int, int, int, void, void, void>>, mp_list<int, void>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, mp_list<void const>>, mp_list<void, int, void const>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, mp_list<void const, int const>>, mp_list<void, int, void const, int const>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, mp_list<int, char[], int, char[], void, char[], void, char[]>>, mp_list<int, char[], void>>));
    }

    {
        using L4 = mp_list<void, int, char[]>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4>, L4>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, mp_list<>>, L4>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, mp_list<void>>, mp_list<int, char[], void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, mp_list<int>>, mp_list<void, char[], int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, mp_list<char[]>>, mp_list<void, int, char[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, mp_list<void, int, char[], void, int, char[]>>, L4>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, mp_list<void const>>, mp_list<void, int, char[], void const>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, mp_list<void const, int const, char const[]>>, mp_list<void, int, char[], void const, int const, char const[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, mp_list<void, void const, int, int const, char[], char const[]>>, mp_list<void, void const, int, int const, char [], char const []>>));
    }

    //

    {
        using L1 = std::tuple<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1,  L1>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, std::tuple<void>>, std::tuple<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, std::tuple<int>>, std::tuple<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, std::tuple<void, int>>, std::tuple<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, std::tuple<void, int, char[]>>, std::tuple<void, int, char[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L1, std::tuple<void, int, void, int, void, int>>, std::tuple<void, int>>));
    }

    {
        using L2 = std::tuple<void>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2>, L2>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, std::tuple<>>, L2>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, std::tuple<void>>, std::tuple<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, std::tuple<int>>, std::tuple<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, std::tuple<void, int>>, std::tuple<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L2, std::tuple<void, void, void, int, int, int>>, std::tuple<void, int>>));
    }

    {
        using L3 = std::tuple<void, int>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3>, L3>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, std::tuple<>>, L3>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, std::tuple<void>>, std::tuple<int, void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, std::tuple<int>>, std::tuple<void, int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, std::tuple<int, int, int, void, void, void>>, std::tuple<int, void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, std::tuple<void const>>, std::tuple<void, int, void const>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, std::tuple<void const, int const>>, std::tuple<void, int, void const, int const>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L3, std::tuple<int, char[], int, char[], void, char[], void, char[]>>, std::tuple<int, char[], void>>));
    }

    {
        using L4 = std::tuple<void, int, char[]>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4>, L4>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, std::tuple<>>, L4>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, std::tuple<void>>, std::tuple<int, char[], void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, std::tuple<int>>, std::tuple<void, char[], int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, std::tuple<char[]>>, std::tuple<void, int, char[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, std::tuple<void, int, char[], void, int, char[]>>, L4>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, std::tuple<void const>>, std::tuple<void, int, char[], void const>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, std::tuple<void const, int const, char const[]>>, std::tuple<void, int, char[], void const, int const, char const[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_symmetric_difference<L4, std::tuple<void, void const, int, int const, char[], char const[]>>, std::tuple<void, void const, int, int const, char [], char const []>>));
    }

    return boost::report_errors();
}
