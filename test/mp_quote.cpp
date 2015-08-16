
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/utility.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>

struct X {};

int main()
{
    using boost::mp_identity_t;
    using boost::mp_quote;
    using boost::mp_unquote;

    using Q = mp_quote<mp_identity_t>;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unquote<Q, void>, void>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_unquote<Q, int[]>, int[]>));

    return boost::report_errors();
}
