# Some frequently used options to speed up the build process.
#
# Only consider Linux support.

option(
    XXX_USE_SPLIT_DWARF
    "Use -gsplit-dwarf when compiling and --gdb-index when linking."
    OFF
)
if (XXX_USE_SPLIT_DWARF)
    add_compile_options(-gsplit-dwarf)
    add_link_options(LINKER:--gdb-index)
endif()

# TODO: precompiled headers
