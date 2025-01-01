// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/config.hpp>

#if !defined(BOOST_MP11_HAS_TEMPLATE_AUTO)

#pragma message("Test skipped because BOOST_MP11_HAS_TEMPLATE_AUTO is not defined")
int main() {}

#else

#ifdef BOOST_USE_MODULES
import std;
import boost.core;
import boost.mp11;
#include <boost/core/lightweight_test_trait_macros.hpp>
#else
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#endif


template<auto... A> struct V1 {};
template<int... I> struct V2 {};

int main()
{
    using boost::mp11::mp_fill;
    using boost::mp11::mp_int;

    BOOST_TEST_TRAIT_SAME(mp_fill<V1<>, mp_int<-1>>, V1<>);
    BOOST_TEST_TRAIT_SAME(mp_fill<V1<false>, mp_int<-1>>, V1<-1>);
    BOOST_TEST_TRAIT_SAME(mp_fill<V1<false, 0>, mp_int<-1>>, V1<-1, -1>);
    BOOST_TEST_TRAIT_SAME(mp_fill<V1<false, 0, true>, mp_int<-1>>, V1<-1, -1, -1>);
    BOOST_TEST_TRAIT_SAME(mp_fill<V1<false, 0, true, std::size_t(1)>, mp_int<-1>>, V1<-1, -1, -1, -1>);

    BOOST_TEST_TRAIT_SAME(mp_fill<V2<>, mp_int<-1>>, V2<>);
    BOOST_TEST_TRAIT_SAME(mp_fill<V2<0>, mp_int<-1>>, V2<-1>);
    BOOST_TEST_TRAIT_SAME(mp_fill<V2<0, 1>, mp_int<-1>>, V2<-1, -1>);
    BOOST_TEST_TRAIT_SAME(mp_fill<V2<0, 1, 2>, mp_int<-1>>, V2<-1, -1, -1>);
    BOOST_TEST_TRAIT_SAME(mp_fill<V2<0, 1, 2, 3>, mp_int<-1>>, V2<-1, -1, -1, -1>);

    return boost::report_errors();
}

#endif
