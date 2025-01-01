
// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifdef BOOST_USE_MODULES
import boost.core;
#include <boost/core/lightweight_test_macros.hpp>
#else
#include <boost/core/lightweight_test.hpp>
#endif

#include <boost/version.hpp>
#include <boost/mp11/version.hpp>


int main()
{
    BOOST_TEST_EQ( BOOST_MP11_VERSION, BOOST_VERSION );
    return boost::report_errors();
}
