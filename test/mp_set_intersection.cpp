
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
    using boost::mp11::mp_set_intersection;

    {
        using L1 = mp_list<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1,  L1>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, mp_list<void>>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, mp_list<int>>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, mp_list<void, int>>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, mp_list<void, int, char[]>>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, mp_list<void, int, void, int, void, int>>, L1>));
    }

    {
        using L2 = mp_list<void>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, mp_list<>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, mp_list<void>>, mp_list<void>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, mp_list<int>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, mp_list<void, int>>, mp_list<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, mp_list<void, void, void, int, int, int>>, mp_list<void>>));
    }

    {
        using L3 = mp_list<void, int>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, mp_list<>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, mp_list<void>>, mp_list<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, mp_list<int>>, mp_list<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, mp_list<int, int, int, void, void, void>>, L3>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, mp_list<void const>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, mp_list<void const, int const>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, mp_list<int, char[], int, char[], void, char[], void, char[]>>, mp_list<void, int>>));
    }

    {
        using L4 = mp_list<void, int, char[]>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, mp_list<>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, mp_list<void>>, mp_list<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, mp_list<int>>, mp_list<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, mp_list<char[]>>, mp_list<char[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, mp_list<void, int, char[], void, int, char[]>>, L4>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, mp_list<void const>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, mp_list<void const, int const, char const[]>>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, mp_list<void, void const, int, int const, char[], char const[]>>, L4>));
    }

    //

    {
        using L1 = std::tuple<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1,  L1>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, std::tuple<void>>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, std::tuple<int>>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, std::tuple<void, int>>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, std::tuple<void, int, char[]>>, L1>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L1, std::tuple<void, int, void, int, void, int>>, L1>));
    }

    {
        using L2 = std::tuple<void>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, std::tuple<void>>, std::tuple<void>>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, std::tuple<int>>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, std::tuple<void, int>>, std::tuple<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L2, std::tuple<void, void, void, int, int, int>>, std::tuple<void>>));
    }

    {
        using L3 = std::tuple<void, int>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, std::tuple<void>>, std::tuple<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, std::tuple<int>>, std::tuple<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, std::tuple<int, int, int, void, void, void>>, L3>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, std::tuple<void const>>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, std::tuple<void const, int const>>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L3, std::tuple<int, char[], int, char[], void, char[], void, char[]>>, std::tuple<void, int>>));
    }

    {
        using L4 = std::tuple<void, int, char[]>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, std::tuple<void>>, std::tuple<void>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, std::tuple<int>>, std::tuple<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, std::tuple<char[]>>, std::tuple<char[]>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, std::tuple<void, int, char[], void, int, char[]>>, L4>));

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, std::tuple<void const>>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, std::tuple<void const, int const, char const[]>>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_set_intersection<L4, std::tuple<void, void const, int, int const, char[], char const[]>>, L4>));
    }

    return boost::report_errors();
}
