
//  Copyright 2021 Kris Jusiak.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/core/lightweight_test_trait.hpp>

int main()
{
#if defined(BOOST_MP11_HAS_NONTYPE_TEMPLATE_ARGS) && defined(BOOST_MP11_HAS_NONTYPE_TEMPLATE_PARAMETER_AUTO)
    using boost::mp11::mp_list;
    using boost::mp11::mp_transform_q;
    using boost::mp11::mp_quote_expr;

    constexpr auto expr = [](auto t) { return t; };

    {
      BOOST_TEST_TRAIT_TRUE((std::is_same<
        mp_list<>,
        mp_transform_q<
          mp_quote_expr<expr>,
          mp_list<>
        >
      >));
    }

    {
      BOOST_TEST_TRAIT_TRUE((std::is_same<
        mp_list<int>,
        mp_transform_q<
          mp_quote_expr<expr>,
          mp_list<int>
        >
      >));
    }

    struct a{};
    struct b{};

    {
      BOOST_TEST_TRAIT_TRUE((std::is_same<
        mp_list<a, b>,
        mp_transform_q<
          mp_quote_expr<expr>,
          mp_list<a, b>
        >
      >));
    }

    {
      constexpr auto to_ptr = [](auto& t) { return &t; };

      BOOST_TEST_TRAIT_TRUE((std::is_same<
        mp_list<a*, b*>,
        mp_transform_q<
          mp_quote_expr<to_ptr>,
          mp_list<a, b>
        >
      >));
    }
#endif
    return boost::report_errors();
}
