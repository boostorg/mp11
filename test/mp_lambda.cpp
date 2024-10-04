
// Copyright 2024 Joaquin M Lopez Munoz.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/lambda.hpp>
#include <boost/mp11/detail/config.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <tuple>
#include <type_traits>
#include <utility>

struct X;
enum E {};

#if BOOST_MP11_WORKAROUND(BOOST_MP11_GCC, < 40900)
// A bug in GCC < 4.9 results in const/volatile qualifiers being stripped
#define CONST
#define VOLATILE
#else
#define CONST const
#define VOLATILE volatile
#endif

int main()
{
    using namespace boost::mp11;

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<int>::fn<>, int>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<int>::fn<void>, int>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<int*>::fn<void>, int*>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<X>::fn<>, X>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<X>::fn<void>, X>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<X*>::fn<void>, X*>));

#if !BOOST_MP11_WORKAROUND(BOOST_MP11_GCC, < 40900)
    // GCC < 4.9 ICEs when dealing with enum types
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<E>::fn<void>, E>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<E*>::fn<void>, E*>));
#endif

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1>::fn<int>, int>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_2>::fn<void, int>, int>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<const _1>::fn<int>, CONST int>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<volatile _1>::fn<int>, VOLATILE int>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<const volatile _2>::fn<void, int>, CONST VOLATILE int>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1*>::fn<int>, int*>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<const _1*>::fn<int>, CONST int*>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<const _1* const>::fn<int>, CONST int* CONST>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<const _1*>::fn<void>, CONST void*>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1&>::fn<int>, int&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<volatile _1*&>::fn<int>, VOLATILE int*&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1&&>::fn<int>, int&&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<volatile _1*&&>::fn<int>, VOLATILE int*&&>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1[]>::fn<int>, int[]>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1[5]>::fn<int>, int[5]>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1*[][5]>::fn<int>, int*[][5]>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2, _3)>::fn<int, char, double>, int(char, double)>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<int(_2)>::fn<void, char>, int(char)>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(void)>::fn<void>, void()>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2, ...)>::fn<int, char>, int(char, ...)>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2, _2*)>::fn<int, char>, int(char, char*)>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(*[])(_2)>::fn<int, char>, int(*[])(char)>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(X::*)(_2, ...)>::fn<int, char>, int(X::*)(char, ...)>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2)>::fn<int, void>, int(void)>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const>::fn<int, void>, int(void) const>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) volatile>::fn<int, void>, int(void) volatile>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const volatile>::fn<int, void>, int(void) const volatile>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2)&>::fn<int, void>, int(void)&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const&>::fn<int, void>, int(void) const&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) volatile&>::fn<int, void>, int(void) volatile&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const volatile&>::fn<int, void>, int(void) const volatile&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2)&&>::fn<int, void>, int(void)&&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const&&>::fn<int, void>, int(void) const&&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) volatile&&>::fn<int, void>, int(void) volatile&&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const volatile&&>::fn<int, void>, int(void) const volatile&&>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) noexcept>::fn<int, void>, int(void) noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const noexcept>::fn<int, void>, int(void) const noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) volatile noexcept>::fn<int, void>, int(void) volatile noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const volatile noexcept>::fn<int, void>, int(void) const volatile noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2)& noexcept>::fn<int, void>, int(void)& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const& noexcept>::fn<int, void>, int(void) const& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) volatile& noexcept>::fn<int, void>, int(void) volatile& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const volatile& noexcept>::fn<int, void>, int(void) const volatile& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2)&& noexcept>::fn<int, void>, int(void)&& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const&& noexcept>::fn<int, void>, int(void) const&& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) volatile&& noexcept>::fn<int, void>, int(void) volatile&& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1(_2) const volatile&& noexcept>::fn<int, void>, int(void) const volatile&& noexcept >));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2)>::fn<int, void, X>, int (X::*)(void)>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const>::fn<int, void, X>, int (X::*)(void) const>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) volatile>::fn<int, void, X>, int (X::*)(void) volatile>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const volatile>::fn<int, void, X>, int (X::*)(void) const volatile>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2)&>::fn<int, void, X>, int (X::*)(void)&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const&>::fn<int, void, X>, int (X::*)(void) const&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) volatile&>::fn<int, void, X>, int (X::*)(void) volatile&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const volatile&>::fn<int, void, X>, int (X::*)(void) const volatile&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2)&&>::fn<int, void, X>, int (X::*)(void)&&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const&&>::fn<int, void, X>, int (X::*)(void) const&&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) volatile&&>::fn<int, void, X>, int (X::*)(void) volatile&&>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const volatile&&>::fn<int, void, X>, int (X::*)(void) const volatile&&>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) noexcept>::fn<int, void, X>, int (X::*)(void) noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const noexcept>::fn<int, void, X>, int (X::*)(void) const noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) volatile noexcept>::fn<int, void, X>, int (X::*)(void) volatile noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const volatile noexcept>::fn<int, void, X>, int (X::*)(void) const volatile noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2)& noexcept>::fn<int, void, X>, int (X::*)(void)& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const& noexcept>::fn<int, void, X>, int (X::*)(void) const& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) volatile& noexcept>::fn<int, void, X>, int (X::*)(void) volatile& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const volatile& noexcept>::fn<int, void, X>, int (X::*)(void) const volatile& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2)&& noexcept>::fn<int, void, X>, int (X::*)(void)&& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const&& noexcept>::fn<int, void, X>, int (X::*)(void) const&& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) volatile&& noexcept>::fn<int, void, X>, int (X::*)(void) volatile&& noexcept >));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_3::*)(_2) const volatile&& noexcept>::fn<int, void, X>, int (X::*)(void) const volatile&& noexcept >));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<_1 (_2::*)>::fn<int, X>, int (X::*)>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<std::pair<_1, _2>>::fn<char, int>, std::pair<char, int>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<std::pair<_2, _1>>::fn<char, int>, std::pair<int, char>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<std::pair<const _1*, _2&>>::fn<char, int>, std::pair<CONST char*, int&>>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<std::tuple<_1, _2>>::fn<char, int>, std::tuple<char, int>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<std::tuple<_2, _1>*>::fn<X, int>, std::tuple<int, X>*>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<std::tuple<const _1*, _2&>*>::fn<char, int>, std::tuple<CONST char*, int&>*>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<std::tuple<_3, std::pair<_2, _1>>>::fn<char, int, double>, std::tuple<double, std::pair<int, char>>>));

    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<std::tuple<_1, _2>>::fn<_2, _1>, std::tuple<_2, _1>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<mp_lambda<mp_bind<std::pair, _1, _2>>::fn<char, int>, mp_bind<std::pair, _1, _2>>));

    //

    return boost::report_errors();
}