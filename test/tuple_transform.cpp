
// Copyright 2020 Hans Dembinski.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/tuple.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <tuple>
#include <memory>
#include <utility>
#include <array>
#include <iosfwd>

// family of test types with state
template <int N>
struct T {
    int value = N;
};

template <int N>
std::ostream& operator<<( std::ostream& os, T<N> const& t )
{
    os << t.value;
    return os;
}

// function changes type and value
struct F {
    template <int N> T<N+1> operator()( T<N> const& t) const
    {
        T<N+1> r;
        ++r.value;
        return r;
    }
};

struct ostreamer {
    std::ostream& os_;
    ostreamer(std::ostream& os) : os_(os) {}
    template <class T> void operator()( T const& t ) const
    {
        os_ << t << " ";
    }
};

int main()
{
    using boost::mp11::tuple_transform;

    {
        std::tuple<T<1>, T<2>> tp;

        {
            std::tuple<T<2>, T<3>> s = tuple_transform( tp, F{} );
            BOOST_TEST_EQ( std::get<0>(s).value, 3 );
            BOOST_TEST_EQ( std::get<1>(s).value, 4 );
        }

        {
            std::tuple<T<2>, T<3>> s = tuple_transform( std::move(tp), F{} );
            BOOST_TEST_EQ( std::get<0>(s).value, 3 );
            BOOST_TEST_EQ( std::get<1>(s).value, 4 );
        }
    }

    {
        std::tuple<T<1>, T<2>> const tp;

        {
            std::tuple<T<2>, T<3>> s = tuple_transform( tp , F{} );
            BOOST_TEST_EQ( std::get<0>(s).value, 3 );
            BOOST_TEST_EQ( std::get<1>(s).value, 4 );
        }

        {
            std::tuple<T<2>, T<3>> s = tuple_transform( std::move(tp) , F{} );
            BOOST_TEST_EQ( std::get<0>(s).value, 3 );
            BOOST_TEST_EQ( std::get<1>(s).value, 4 );
        }
    }

    {
        std::pair<T<1>, T<2>> tp;

        {
            std::pair<T<2>, T<3>> s = tuple_transform( tp, F{} );
            BOOST_TEST_EQ( std::get<0>(s).value, 3 );
            BOOST_TEST_EQ( std::get<1>(s).value, 4 );
        }

        {
            std::pair<T<2>, T<3>> s = tuple_transform( tp, F{} );
            BOOST_TEST_EQ( std::get<0>(s).value, 3 );
            BOOST_TEST_EQ( std::get<1>(s).value, 4 );
        }
    }

    {
        std::tuple<> tp;

        {
            auto s = tuple_transform( tp, F{} );
            BOOST_TEST_TRAIT_TRUE((std::is_same<decltype(s), std::tuple<>>));
        }

        {
            auto s = tuple_transform( std::move(tp), F{} );
            BOOST_TEST_TRAIT_TRUE((std::is_same<decltype(s), std::tuple<>>));
        }
    }

    return boost::report_errors();
}
