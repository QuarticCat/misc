# Some frequently used cmake arguments.
#
# Although I wrote a script here, I only use it by copying and pasting
# arguments listed below.
#
# Only consider Linux support.

args=(
    # Use ninja
    -G=Ninja

    # Release build
    -DCMAKE_BUILD_TYPE=Release

    # Generate compilation database
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

    # Use clang
    -DCMAKE_CXX_COMPILER='clang++'

    # Use ccache (or distcc, icecream)
    -DCMAKE_CXX_COMPILER_LAUNCHER='ccache'

    # Use lld (or mold)
    -DCMAKE_EXE_LINKER_FLAGS='-fuse-ld=lld'

    # Enable split dwarf
    -DCMAKE_CXX_FLAGS='-gsplit-dwarf'
    -DCMAKE_EXE_LINKER_FLAGS='-Wl,--gdb-index'

    # Enable unity build
    -DCMAKE_UNITY_BUILD=ON
    -DCMAKE_UNITY_BUILD_BATCH_SIZE=5

    # Enable LTO
    -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON

    # Enable PGO
    # See https://clang.llvm.org/docs/UsersManual.html#profile-guided-optimization
)

declare -A arg_map
for i in $args; {
    IFS='=' read -r key value <<< $i
    if (( $+arg_map[$key] )) {
        arg_map[$key]+=" $value"
    } else {
        arg_map[$key]="$value"
    }
}

args=()
for k v in ${(kv)arg_map}; {
    args+="$k='$v'"
}

echo $args
