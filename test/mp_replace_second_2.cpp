// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/config.hpp>

#if !defined(BOOST_MP11_HAS_TEMPLATE_AUTO)

#pragma message("Test skipped because BOOST_MP11_HAS_TEMPLATE_AUTO is not defined")
int main() {}

#else

#include <boost/mp11/list.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/core/lightweight_test_trait.hpp>

template<auto... A> struct L1 {};
template<int... I> struct L2 {};

int main()
{
    using boost::mp11::mp_replace_second;
    using boost::mp11::mp_size_t;
    using boost::mp11::mp_int;

    //

    BOOST_TEST_TRAIT_SAME(mp_replace_second<L1<0, 1>, mp_size_t<0>>, L1<0, std::size_t(0)>);
    BOOST_TEST_TRAIT_SAME(mp_replace_second<L1<0, 1, false>, mp_size_t<0>>, L1<0, std::size_t(0), false>);
    BOOST_TEST_TRAIT_SAME(mp_replace_second<L1<0, 1, false, true>, mp_size_t<0>>, L1<0, std::size_t(0), false, true>);

    //

    BOOST_TEST_TRAIT_SAME(mp_replace_second<L2<0, 1>, mp_int<-1>>, L2<0, -1>);
    BOOST_TEST_TRAIT_SAME(mp_replace_second<L2<0, 1, 2>, mp_int<-1>>, L2<0, -1, 2>);
    BOOST_TEST_TRAIT_SAME(mp_replace_second<L2<0, 1, 2, 3>, mp_int<-1>>, L2<0, -1, 2, 3>);

    //

    return boost::report_errors();
}

#endif
