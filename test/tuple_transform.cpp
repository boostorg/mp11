
// Copyright 2020 Hans Dembinski.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/tuple.hpp>
#include <boost/core/lightweight_test.hpp>
#include <tuple>
#include <memory>
#include <utility>
#include <array>

template <int N>
struct T {
    int value;
    
    T() = default;
    T(int v) : value(v) {};
    T& operator=(int v) { value = v; return *this; };
    
    operator int() const { return value; }
};

struct F {
    template <int N>
    T<N+1> operator()(const T<N>& t) const {
        return t.value - 1;
    }
};

int main()
{
    using boost::mp11::tuple_transform;

    {
        std::tuple<T<1>, T<2>> tp{ 2, 1 };

        {
            std::tuple<T<2>, T<3>> s = tuple_transform( F{}, tp );
            BOOST_TEST_EQ( std::get<0>(s), 1 );
            BOOST_TEST_EQ( std::get<1>(s), 0 );
        }

        {
            std::tuple<T<2>, T<3>> s = tuple_transform( F{}, std::move(tp) );
            BOOST_TEST_EQ( std::get<0>(s), 1 );
            BOOST_TEST_EQ( std::get<1>(s), 0 );
        }
    }

    {
        std::tuple<T<1>, T<2>> const tp{ 2, 1 };

        {
            std::tuple<T<2>, T<3>> s = tuple_transform( F{}, tp );
            BOOST_TEST_EQ( std::get<0>(s), 1 );
            BOOST_TEST_EQ( std::get<1>(s), 0 );
        }

        {
            std::tuple<T<2>, T<3>> s = tuple_transform( F{}, std::move(tp) );
            BOOST_TEST_EQ( std::get<0>(s), 1 );
            BOOST_TEST_EQ( std::get<1>(s), 0 );
        }
    }

    {
        std::pair<T<1>, T<2>> tp{ 2, 1 };

        {
            std::pair<T<2>, T<3>> s = tuple_transform( F{}, tp );
            BOOST_TEST_EQ( std::get<0>(s), 1 );
            BOOST_TEST_EQ( std::get<1>(s), 0 );
        }

        {
            std::pair<T<2>, T<3>> s = tuple_transform( F{}, tp );
            BOOST_TEST_EQ( std::get<0>(s), 1 );
            BOOST_TEST_EQ( std::get<1>(s), 0 );
        }
    }

    {
        std::tuple<> tp;

        BOOST_TEST_EQ( tuple_transform( F{}, tp ), std::tuple<>{} );
        BOOST_TEST_EQ( tuple_transform( F{}, std::move( tp ) ), std::tuple<>{} );
    }

    return boost::report_errors();
}
