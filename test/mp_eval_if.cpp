
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/core/lightweight_test_trait.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/integral.hpp>
#include <type_traits>

int main()
{
    using boost::mp_eval_if_c;
    using boost::mp_identity;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_eval_if_c<true, char[], mp_identity, void, void, void>, char[]>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_eval_if_c<false, char[], mp_identity, void()>, mp_identity<void()>>));

    using boost::mp_eval_if;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_eval_if<std::true_type, char[], mp_identity, void, void, void>, char[]>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_eval_if<std::false_type, char[], mp_identity, void()>, mp_identity<void()>>));

    using boost::mp_int;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_eval_if<mp_int<-7>, char[], mp_identity, void, void, void>, char[]>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_eval_if<mp_int<0>, char[], mp_identity, void()>, mp_identity<void()>>));

    using boost::mp_size_t;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_eval_if<mp_size_t<14>, char[], mp_identity, void, void, void>, char[]>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_eval_if<mp_size_t<0>, char[], mp_identity, void()>, mp_identity<void()>>));

    return boost::report_errors();
}
