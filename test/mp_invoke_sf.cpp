
// Copyright 2015, 2017 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/utility.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>

using boost::mp11::mp_invoke;
using boost::mp11::mp_quote;
using boost::mp11::mp_valid;
using boost::mp11::mp_identity_t;

int main()
{
    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_invoke>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_invoke, void>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_invoke, void, void>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_invoke, void, void, void>));

    using Qi = mp_quote<mp_identity_t>;

    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_invoke, Qi>));
    BOOST_TEST_TRAIT_TRUE((mp_valid<mp_invoke, Qi, void>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_invoke, Qi, void, void>));

    return boost::report_errors();
}
