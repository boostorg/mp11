
// Copyright 2020 Hans Dembinski.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/tuple.hpp>
#include <boost/mp11/detail/config.hpp>

// Technically std::tuple isn't constexpr enabled in C++11, but it works with libstdc++

#if defined( BOOST_MP11_NO_CONSTEXPR ) || ( !defined( __GLIBCXX__ ) && __cplusplus < 201400L )

int main() {}

#else

#include <tuple>
#include <type_traits>

struct F
{
    template<class T> constexpr bool operator()( T ) const
    {
        return std::is_integral<T>::value;
    }
};

int main()
{
    {
        constexpr std::tuple<int, float> tp;
        constexpr std::tuple<bool, bool> r = boost::mp11::tuple_transform( tp, F{} );
        static_assert(std::get<0>(r).value == true, "get<0>(r).value == true" );
        static_assert(std::get<1>(r).value == false, "get<1>(r).value == false" );
    }

#if defined( __clang_major__ ) && __clang_major__ == 3 && __clang_minor__ < 9
// "error: default initialization of an object of const type 'const std::tuple<>' without a user-provided default constructor"
#else

    {
        constexpr std::tuple<> tp;
        constexpr std::tuple<> r = boost::mp11::tuple_transform( tp, F{} );
        void(r);
    }

#endif
}

#endif
