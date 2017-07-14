# Mp11, a C++11 metaprogramming library

Mp11 is a C++11 metaprogramming library based on template aliases and variadic templates.
It implements the approach outlined in the article
["Simple C++11 metaprogramming"](http://pdimov.com/cpp2/simple_cxx11_metaprogramming.html)
and [its sequel](http://pdimov.com/cpp2/simple_cxx11_metaprogramming_2.html). Reading these
articles before proceeding with the documentation is _highly_ recommended.

The library is intended to be placed in a subdirectory `libs/mp11` in a Boost distribution,
but can also be used standalone, although it does require Boost.Config. A single-header form
is available in [include/boost/mp11_single.hpp](include/boost/mp11_single.hpp).

The Mp11 documentation is included in the repository and [can be browsed here](https://rawgit.com/pdimov/mp11/master/doc/html/mp11.html).

## Supported compilers

* g++ 4.7 or later
* clang++ 3.5 or later
* Visual Studio 2013, 2015, 2017

Tested on [Travis](https://travis-ci.org/pdimov/mp11/) and [Appveyor](https://ci.appveyor.com/project/pdimov/mp11/).

## License

Distributed under the [Boost Software License, Version 1.0](http://boost.org/LICENSE_1_0.txt).
