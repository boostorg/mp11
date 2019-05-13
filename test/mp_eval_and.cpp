
// Copyright 2019 Hans Dembinski.
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
    using boost::mp11::mp_eval_and;

    BOOST_TEST_TRAIT_TRUE((mp_eval_and<char>));

    BOOST_TEST_TRAIT_TRUE((mp_eval_and<int, std::is_integral, std::is_signed>));
    BOOST_TEST_TRAIT_FALSE((mp_eval_and<unsigned, std::is_integral, std::is_signed>));
    BOOST_TEST_TRAIT_FALSE((mp_eval_and<float, std::is_integral, std::is_signed>));
    BOOST_TEST_TRAIT_FALSE((mp_eval_and<char[], std::is_integral, std::is_unsigned>));

    return boost::report_errors();
}
