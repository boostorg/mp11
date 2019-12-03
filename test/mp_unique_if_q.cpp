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

struct is_same_size
{
    template<class TLhs, class TRhs>
    struct impl : boost::mp11::mp_bool<sizeof(TLhs) == sizeof(TRhs)> {};
    template<class TLhs, class TRhs> using fn = typename impl<TLhs, TRhs>::type;
};

int main()
{
    using boost::mp11::mp_list;
    using boost::mp11::mp_unique_if_q;

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<mp_list<>, is_same_size>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<mp_list<int>, is_same_size>, mp_list<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<mp_list<int, int>, is_same_size>, mp_list<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<mp_list<char, bool>, is_same_size>, mp_list<char>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<mp_list<bool, char>, is_same_size>, mp_list<bool>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<mp_list<bool, char, bool>, is_same_size>, mp_list<bool>>));
        struct foo{};
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<mp_list<char, bool, int, foo>, is_same_size>, mp_list<char, int>>));
    }

    {
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<std::tuple<>, is_same_size>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<std::tuple<int>, is_same_size>, std::tuple<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<std::tuple<int, int>, is_same_size>, std::tuple<int>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<std::tuple<char, bool>, is_same_size>, std::tuple<char>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<std::tuple<bool, char>, is_same_size>, std::tuple<bool>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<std::tuple<bool, char, bool>, is_same_size>, std::tuple<bool>>));
        struct foo{};
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unique_if_q<std::tuple<char, bool, int, foo>, is_same_size>, std::tuple<char, int>>));
    }

    return boost::report_errors();
}
