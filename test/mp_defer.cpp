
// Copyright 2015-2017 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/utility.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <type_traits>

using boost::mp11::mp_identity;
using boost::mp11::mp_true;
using boost::mp11::mp_false;

template<class T> struct has_type
{
    template<class U> static mp_true f( mp_identity<typename U::type>* );
    template<class U> static mp_false f( ... );

    using type = decltype( f<T>(0) );

#if BOOST_WORKAROUND( BOOST_GCC, < 40800 )

    static constexpr auto value = type::value;

#else

    static const auto value = type::value;

#endif
};

using boost::mp11::mp_defer;

template<class T> using add_pointer = T*;
template<class... T> using add_pointer_impl = mp_defer<add_pointer, T...>;

int main()
{
    BOOST_TEST_TRAIT_TRUE((has_type<add_pointer_impl<void>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<add_pointer_impl<void>::type, void*>));

    BOOST_TEST_TRAIT_TRUE((has_type<add_pointer_impl<int>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<add_pointer_impl<int>::type, int*>));

    BOOST_TEST_TRAIT_FALSE((has_type<add_pointer_impl<>>));
    BOOST_TEST_TRAIT_FALSE((has_type<add_pointer_impl<void, void>>));

    return boost::report_errors();
}
