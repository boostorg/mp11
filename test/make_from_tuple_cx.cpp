
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/tuple.hpp>
#include <boost/config.hpp>

// Technically std::tuple isn't constexpr enabled in C++11, but it works with libstdc++

#if defined( BOOST_NO_CXX11_CONSTEXPR ) || ( defined( _LIBCPP_VERSION ) && __cplusplus < 201400L )

int main() {}

#else

#include <tuple>
#include <array>
#include <utility>

struct T1
{
    int x, y, z;

    constexpr T1( int x = 0, int y = 0, int z = 0 ): x(x), y(y), z(z) {}
};

int main()
{
    using boost::mp11::make_from_tuple;

    {
        constexpr std::tuple<int, short, char> tp{ 1, 2, 3 };

        constexpr auto r = make_from_tuple<T1>( tp );

        static_assert( r.x == 1, "r.x == 1" );
        static_assert( r.y == 2, "r.y == 2" );
        static_assert( r.z == 3, "r.z == 3" );
    }

    {
        constexpr std::pair<short, char> tp{ 1, 2 };

        constexpr auto r = make_from_tuple<T1>( tp );

        static_assert( r.x == 1, "r.x == 1" );
        static_assert( r.y == 2, "r.y == 2" );
        static_assert( r.z == 0, "r.z == 0" );
    }

    {
        constexpr std::array<short, 3> tp{{ 1, 2, 3 }};

        constexpr auto r = make_from_tuple<T1>( tp );

        static_assert( r.x == 1, "r.x == 1" );
        static_assert( r.y == 2, "r.y == 2" );
        static_assert( r.z == 3, "r.z == 3" );
    }

    {
        constexpr std::tuple<> tp;

        constexpr auto r = make_from_tuple<T1>( tp );

        static_assert( r.x == 0, "r.x == 0" );
        static_assert( r.y == 0, "r.y == 0" );
        static_assert( r.z == 0, "r.z == 0" );
    }
}

#endif
