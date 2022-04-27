# Some frequently used command arguments to speed up the build process.
#
# Written in env variables. Can also be written in CMake presets.
#
# Only consider Linux support.

export CMAKE_GENERATOR='Ninja'
export CMAKE_CXX_COMPILER_LAUNCHER='ccache'  # or distcc, icecream
export CMAKE_CXX_FLAGS='-fuse-ld=lld'  # or mold
