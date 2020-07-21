
// Copyright 2016, 2020 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/map.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <tuple>

struct Foo {};
struct Bar {};

int main()
{
    using boost::mp11::mp_map_find;

    using L1 = std::tuple<std::tuple<int, int>, std::tuple<long, long>, std::tuple<bool, Foo>, std::tuple<Foo, bool>>;

    BOOST_TEST_TRAIT_SAME( mp_map_find<L1, int>, std::tuple<int, int> );
    BOOST_TEST_TRAIT_SAME( mp_map_find<L1, bool>, std::tuple<bool, Foo> );
    BOOST_TEST_TRAIT_SAME( mp_map_find<L1, Foo>, std::tuple<Foo, bool> );

    using L2 = std::tuple<std::tuple<Foo, Bar>, std::tuple<Bar, Foo>>;

    BOOST_TEST_TRAIT_SAME( mp_map_find<L2, Foo>, std::tuple<Foo, Bar> );
    BOOST_TEST_TRAIT_SAME( mp_map_find<L2, Bar>, std::tuple<Bar, Foo> );

    return boost::report_errors();
}
