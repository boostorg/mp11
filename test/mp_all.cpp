
// Copyright 2015, 2016 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/function.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>

int main()
{
    using boost::mp11::mp_all;
    using boost::mp11::mp_true;
    using boost::mp11::mp_false;
    using boost::mp11::mp_int;
    using boost::mp11::mp_size_t;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<>, mp_true>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_true>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_false>, mp_false>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_int<-7>>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_int<0>>, mp_false>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_size_t<7>>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_size_t<0>>, mp_false>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_true, mp_true>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_false, mp_true>, mp_false>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_true, mp_false>, mp_false>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_false, mp_false>, mp_false>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_int<-7>, mp_int<7>>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_size_t<(size_t)-1>, mp_size_t<1>>, mp_true>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_true, mp_true, mp_true>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_true, mp_false, mp_true>, mp_false>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_false, mp_false, mp_false>, mp_false>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_true, mp_true, mp_true, mp_true>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_true, mp_false, mp_true, mp_true>, mp_false>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_false, mp_false, mp_false, mp_false>, mp_false>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_int<1>, mp_int<2>, mp_int<-11>, mp_int<14>>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_int<1>, mp_int<0>, mp_int<-11>, mp_int<14>>, mp_false>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_size_t<1>, mp_size_t<2>, mp_size_t<114>, mp_size_t<8>, mp_size_t<94>>, mp_true>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_all<mp_size_t<1>, mp_size_t<2>, mp_size_t<114>, mp_size_t<0>, mp_size_t<94>>, mp_false>));

    return boost::report_errors();
}
