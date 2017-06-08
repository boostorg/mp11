# Mp11, a C++11 metaprogramming library

Mp11 is a C++11 metaprogramming library based on template aliases and variadic templates.
It implements the approach outlined in the article
["Simple C++11 metaprogramming"](http://pdimov.com/cpp2/simple_cxx11_metaprogramming.html)
and [its sequel](http://pdimov.com/cpp2/simple_cxx11_metaprogramming_2.html). Reading these
articles before proceeding with the documentation is _highly_ recommended.

The library is intended to be placed in a subdirectory `libs/mp11` in a Boost distribution,
but can also be used standalone, although it does require Boost.Config. A single-header form
is available in [include/boost/mp11_single.hpp](include/boost/mp11_single.hpp).

## Supported compilers

* g++ 4.7 or later
* clang++ 3.5 or later
* Visual Studio 2013, 2015, 2017

Tested on [Travis](https://travis-ci.org/pdimov/mp11/) and [Appveyor](https://ci.appveyor.com/project/pdimov/mp11/).

## Documentation

[Overview](doc/mp11/overview.adoc)

[Definitions](doc/mp11/definitions.adoc)

[Examples](doc/mp11/examples.adoc)

[Reference](doc/mp11/reference.adoc)

* [Integral Constants](doc/mp11/integral.adoc)

* [List Operations](doc/mp11/list.adoc)

* [Utility Components](doc/mp11/utility.adoc)

* [Algorithms](doc/mp11/algorithm.adoc)

* [Set Operations](doc/mp11/set.adoc)

* [Map Operations](doc/mp11/map.adoc)

* [Helper Metafunctions](doc/mp11/function.adoc)

* [Bind](doc/mp11/bind.adoc)

* [Integer Sequences](doc/mp11/integer_sequence.adoc)

* [A "for each" algorithm for tuple-like types](doc/mp11/tuple_for_each.adoc)

## License

Distributed under the [Boost Software License, Version 1.0](http://boost.org/LICENSE_1_0.txt).
