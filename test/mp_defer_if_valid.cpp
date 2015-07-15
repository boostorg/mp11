
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/utility.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>

using boost::mp_defer_if_valid;
using boost::mp_identity;

template<class... T> using mp_identity_2 = typename mp_defer_if_valid<mp_identity, T...>::type;

int main()
{
    using boost::mp_valid;

    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_identity_2>));
    BOOST_TEST_TRAIT_TRUE((mp_valid<mp_identity_2, void>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_identity_2<void>, mp_identity<void>>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_identity_2, void, void>));

    return boost::report_errors();
}
