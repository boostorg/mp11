module;

#include <cassert>

export module boost.mp11;
import std;

#define BOOST_MP11_INTERFACE_UNIT

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 5244)
#endif

#include <boost/mp11.hpp>
