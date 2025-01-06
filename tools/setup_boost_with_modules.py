#!/usr/bin/python3

# This is a temporary workaround to make CIs use the
# "Boost with C++20 modules" proposal, instead of the regular develop branch
# Call it instead of depinst

from subprocess import run

def main():

    submodules = [
        ('tools/cmake',         'https://github.com/anarthal/boost-cmake',    'feature/cxx20-modules'),
        ('libs/headers',        'https://github.com/boostorg/headers',        'develop'),
        ('libs/config',         'https://github.com/boostorg/config',         'develop'),
        ('libs/assert',         'https://github.com/anarthal/assert',         'feature/cxx20-modules'),
        ('libs/core',           'https://github.com/anarthal/core',           'feature/cxx20-modules'),
        ('libs/throw_exception','https://github.com/anarthal/throw_exception','feature/cxx20-modules'),
        ('libs/static_assert',  'https://github.com/boostorg/static_assert',  'develop'),
    ]

    for submodule, url, branch in submodules:
        run(["git", "clone", url, "--depth", "1", "-b", branch, submodule])

if __name__ == '__main__':
    main()
