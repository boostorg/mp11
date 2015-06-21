
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/integer_sequence.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>

int main()
{
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<int, 0>, boost::integer_sequence<int>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<int, 1>, boost::integer_sequence<int, 0>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<int, 2>, boost::integer_sequence<int, 0, 1>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<int, 3>, boost::integer_sequence<int, 0, 1, 2>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<int, 4>, boost::integer_sequence<int, 0, 1, 2, 3>>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<char, 0>, boost::integer_sequence<char>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<char, 1>, boost::integer_sequence<char, 0>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<char, 2>, boost::integer_sequence<char, 0, 1>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<char, 3>, boost::integer_sequence<char, 0, 1, 2>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<char, 4>, boost::integer_sequence<char, 0, 1, 2, 3>>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<std::size_t, 0>, boost::integer_sequence<std::size_t>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<std::size_t, 1>, boost::integer_sequence<std::size_t, 0>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<std::size_t, 2>, boost::integer_sequence<std::size_t, 0, 1>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<std::size_t, 3>, boost::integer_sequence<std::size_t, 0, 1, 2>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_integer_sequence<std::size_t, 4>, boost::integer_sequence<std::size_t, 0, 1, 2, 3>>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<0>, boost::integer_sequence<std::size_t>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<1>, boost::integer_sequence<std::size_t, 0>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<2>, boost::integer_sequence<std::size_t, 0, 1>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<3>, boost::integer_sequence<std::size_t, 0, 1, 2>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<4>, boost::integer_sequence<std::size_t, 0, 1, 2, 3>>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<0>, boost::index_sequence<>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<1>, boost::index_sequence<0>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<2>, boost::index_sequence<0, 1>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<3>, boost::index_sequence<0, 1, 2>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::make_index_sequence<4>, boost::index_sequence<0, 1, 2, 3>>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::index_sequence_for<>, boost::index_sequence<>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::index_sequence_for<void>, boost::index_sequence<0>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::index_sequence_for<void, void>, boost::index_sequence<0, 1>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::index_sequence_for<void, void, void>, boost::index_sequence<0, 1, 2>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<boost::index_sequence_for<void, void, void, void>, boost::index_sequence<0, 1, 2, 3>>));

    return boost::report_errors();
}
