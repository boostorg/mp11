
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

int main()
{
    using boost::mp_list;
    using boost::mp_find_if;

    {
        using L1 = mp_list<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if<L1, std::is_const>, L1>));

        using L2 = mp_list<X1, X1 const, X1 const, X1*, X1*, X1*>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if<L2, std::is_volatile>, mp_list<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if<L2, std::is_const>, mp_list<X1 const, X1 const, X1*, X1*, X1*>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if<L2, std::is_pointer>, mp_list<X1*, X1*, X1*>>));
    }

    {
        using L1 = std::tuple<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if<L1, std::is_const>, L1>));

        using L2 = std::tuple<X1, X1 const, X1 const, X1*, X1*, X1*>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if<L2, std::is_volatile>, std::tuple<>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if<L2, std::is_const>, std::tuple<X1 const, X1 const, X1*, X1*, X1*>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if<L2, std::is_pointer>, std::tuple<X1*, X1*, X1*>>));
    }

    return boost::report_errors();
}
