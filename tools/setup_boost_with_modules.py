#!/usr/bin/python3

# This is a temporary workaround to make CIs use the
# "Boost with C++20 modules" proposal, instead of the regular develop branch
# Call it instead of depinst

from subprocess import run
import os

def main():

    submodules = [
        ('tools/cmake',         'https://github.com/anarthal/boost-cmake'),
        ('libs/assert',         'https://github.com/anarthal/assert'),
        ('libs/core',           'https://github.com/anarthal/core'),
        ('libs/throw_exception','https://github.com/anarthal/throw_exception'),
    ]

    for submodule, url in submodules:
        os.chdir(submodule)
        run(['git', 'remote', 'add', 'modules', url])
        run(['git', 'fetch', '--depth', '1', 'modules', 'feature/cxx20-modules'])
        run(['git', 'checkout', 'modules/feature/cxx20-modules'])
        os.chdir('../..')


if __name__ == '__main__':
    main()
