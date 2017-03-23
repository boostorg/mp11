
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/core/lightweight_test_trait.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>
#include <type_traits>
#include <tuple>
#include <utility>

int main()
{
    using boost::mp11::mp_list;
    using boost::mp11::mp_append;
    using boost::mp11::mp_iota_c;
    using boost::mp11::mp_transform;
    using boost::mp11::mp_rename;

    using L1 = mp_iota_c<97>;
    using L2 = mp_transform<mp_list, L1>;

    using L3 = mp_rename<L2, mp_append>;

    BOOST_TEST_TRAIT_TRUE((std::is_same<L3, L1>));

    //

    return boost::report_errors();
}
