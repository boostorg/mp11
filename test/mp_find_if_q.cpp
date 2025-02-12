// Copyright 2015, 2017, 2024 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/bind.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>
#include <tuple>
#include <utility>

struct X1 {};

int main()
{
    using boost::mp11::mp_list;
    using boost::mp11::mp_find_if_q;
    using boost::mp11::mp_size_t;
    using boost::mp11::mp_quote;

    {
        using L1 = mp_list<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L1, mp_quote<std::is_const>>, mp_size_t<0>>));

        using L2 = mp_list<X1, X1 const, X1 const, X1*, X1*, X1*>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_volatile>>, mp_size_t<6>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_const>>, mp_size_t<1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_pointer>>, mp_size_t<3>>));
    }

    {
        using L1 = std::tuple<>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L1, mp_quote<std::is_const>>, mp_size_t<0>>));

        using L2 = std::tuple<X1, X1 const, X1 const, X1*, X1*, X1*>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_volatile>>, mp_size_t<6>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_const>>, mp_size_t<1>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_pointer>>, mp_size_t<3>>));
    }

    {
        using L2 = std::pair<X1 const, X1*>;

        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_volatile>>, mp_size_t<2>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_const>>, mp_size_t<0>>));
        BOOST_TEST_TRAIT_TRUE((std::is_same<mp_find_if_q<L2, mp_quote<std::is_pointer>>, mp_size_t<1>>));
    }

    {
        using boost::mp11::mp_iota_c;
        using boost::mp11::mp_bind_front;
        using boost::mp11::mp_less;

#if !defined( BOOST_MP11_HAS_CXX14_CONSTEXPR )

        int const N = 257;

#else

        int const N = 1089;

#endif

        using L = mp_iota_c<N>;
        using R = mp_find_if_q< L, mp_bind_front<mp_less, mp_size_t<N/2>> >;

        BOOST_TEST_TRAIT_TRUE((std::is_same<R, mp_size_t<N/2+1>>));
    }

    return boost::report_errors();
}
