# Some frequently used cmake arguments.
#
# Although I wrote a script here, I only use it by copying and pasting
# arguments listed below.
#
# Only consider Linux support.

args=(
    # Build dir
    -B=build

    # Use ninja
    -G=Ninja

    # Release build
    -DCMAKE_BUILD_TYPE=Release

    # Generate compilation database
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

    # Use clang
    -DCMAKE_C_COMPILER='clang'
    -DCMAKE_CXX_COMPILER='clang++'
    -DCMAKE_CUDA_COMPILER='clang++'

    # Use ccache (or distcc, icecream)
    -DCMAKE_{C,CXX}_COMPILER_LAUNCHER='ccache'

    # Use lld (or mold)
    -DCMAKE_LINKER_TYPE=LLD  # since 3.29
    # -DCMAKE_{EXE,STATIC,SHARED,MODULE}_LINKER_FLAGS='-fuse-ld=lld'

    # Enable split dwarf
    -DCMAKE_{C,CXX}_FLAGS='-gsplit-dwarf'
    -DCMAKE_{EXE,STATIC,SHARED,MODULE}_LINKER_FLAGS='-Wl,--gdb-index'

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
