#!/bin/bash
#
# Copyright (c) 2026 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

set -e

wget https://github.com/Kitware/CMake/releases/download/v4.2.3/cmake-4.2.3-linux-x86_64.tar.gz
tar -xf cmake-4.2.3-linux-x86_64.tar.gz
mv cmake-4.2.3-linux-x86_64 /opt/cmake
update-alternatives --install /usr/bin/cmake cmake /opt/cmake/bin/cmake 100
update-alternatives --install /usr/bin/ctest ctest /opt/cmake/bin/ctest 100
