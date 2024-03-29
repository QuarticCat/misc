# Misc

Some of my frequently copy-and-pasted code snippets. I hope they will also be helpful to you.

## Install Git Hooks (For Myself)

```console
$ ./.githooks/install_hooks.sh
```

The hooks will automatically generate this README file before commit.

## Table of Contents

- [cmake](./cmake)
  - [args.zsh](./cmake/args.zsh): Some frequently used cmake arguments.
- [cpp](./cpp)
  - [assume.hpp](./cpp/assume.hpp): Provide additional information to compiler.
  - [assume_aligned.hpp](./cpp/assume_aligned.hpp): A C++ wrapper of `__builtin_assume_aligned`.
  - [cache_padded.cpp](./cpp/cache_padded.cpp): An example showing that 128-byte alignment may outperform 64-byte alignment in some cases on Intel (but not on AMD).
  - [ctti.hpp](./cpp/ctti.hpp): Get the name / hash of the given type in compile-time.
  - [endian.hpp](./cpp/endian.hpp): Some endian-ness utilities.
  - [histogram.hpp](./cpp/histogram.hpp): C++ version of TurboHist, the fastest histogram construction.
  - [poor_mans_concept.cpp](./cpp/poor_mans_concept.cpp): An example of how to simulate concept before C++20.
  - [timer.hpp](./cpp/timer.hpp): Some simple timer implementations.
  - [unroll.hpp](./cpp/unroll.hpp): Some unrolling utilities.
  - [vec_ext.hpp](./cpp/vec_ext.hpp): Some vector extension utilities.
- [python](./python)
  - [fill_pool.py](./python/fill_pool.py): An example of how to fill a multi-processing / multi-threading pool with dependent tasks.
  - [quote.py](./python/quote.py): Add / remove quotes (escapes).
- [rust](./rust)
  - [serde_post.rs](./rust/serde_post.rs): An example of how to add post processing into `serde::Deserialize` with minimum code.
  - [serde_shorthand.rs](./rust/serde_shorthand.rs): An example of how to add a shorthand for a struct in `serde`. Shorter and cleaner than https://serde.rs/string-or-struct.html.
  - [trait_alias_with_assoc_bound.rs](./rust/trait_alias_with_assoc_bound.rs): An example of how to implement trait aliases with associated type bounds.