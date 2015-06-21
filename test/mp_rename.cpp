
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/core/lightweight_test_trait.hpp>
#include <boost/mp11/list.hpp>
#include <type_traits>
#include <tuple>
#include <utility>

template<class... T> struct X {};
template<class... T> using Y = X<T...>;

int main()
{
    using boost::mp_list;
    using boost::mp_rename;

    using L1 = mp_list<>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L1, mp_list>, mp_list<>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L1, std::tuple>, std::tuple<>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L1, X>, X<>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L1, Y>, Y<>>));

    using L2 = mp_list<char>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L2, mp_list>, mp_list<char>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L2, std::tuple>, std::tuple<char>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L2, X>, X<char>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L2, Y>, Y<char>>));

    using L3 = mp_list<char, double>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L3, mp_list>, mp_list<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L3, std::tuple>, std::tuple<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L3, X>, X<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L3, Y>, Y<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L3, std::pair>, std::pair<char, double>>));

    using L4 = mp_list<int, char, float>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L4, mp_list>, mp_list<int, char, float>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L4, std::tuple>, std::tuple<int, char, float>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L4, X>, X<int, char, float>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L4, Y>, Y<int, char, float>>));

    //

    using L5 = std::tuple<>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L5, mp_list>, mp_list<>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L5, std::tuple>, std::tuple<>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L5, X>, X<>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L5, Y>, Y<>>));

    using L6 = std::tuple<char>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L6, mp_list>, mp_list<char>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L6, std::tuple>, std::tuple<char>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L6, X>, X<char>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L6, Y>, Y<char>>));

    using L7 = std::tuple<char, double>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L7, mp_list>, mp_list<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L7, std::tuple>, std::tuple<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L7, X>, X<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L7, Y>, Y<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L7, std::pair>, std::pair<char, double>>));

    using L8 = std::tuple<int, char, float>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L8, mp_list>, mp_list<int, char, float>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L8, std::tuple>, std::tuple<int, char, float>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L8, X>, X<int, char, float>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L8, Y>, Y<int, char, float>>));

    //

    using L9 = std::pair<char, double>;
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L9, mp_list>, mp_list<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L9, std::tuple>, std::tuple<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L9, X>, X<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L9, Y>, Y<char, double>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_rename<L9, std::pair>, std::pair<char, double>>));

    //

    return boost::report_errors();
}
