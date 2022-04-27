# Misc

Some of my frequently copy-and-pasted code snippets. I hope they will also be helpful to you.

## Install Git Hooks (For Myself)

```console
$ ./.githooks/install_hooks.sh
```

The hooks will automatically generate this README file before commit.

## Table of Contents

- [cpp](./cpp)
  - [.clang-format](./cpp/.clang-format): My currently favorite code style. Based on clang-format 10.
  - [assume.hpp](./cpp/assume.hpp): Provide additional information to compiler.
  - [assume_aligned.hpp](./cpp/assume_aligned.hpp): A C++ wrapper of `__builtin_assume_aligned`.
  - [ctti.hpp](./cpp/ctti.hpp): Get the name / hash of the given type in compile-time.
  - [endian.hpp](./cpp/endian.hpp): Some endian-ness utilities.
  - [poor_mans_concept.cpp](./cpp/poor_mans_concept.cpp): An example of how to simulate concept before C++20.
- [python](./python)
  - [fill_pool.py](./python/fill_pool.py): An example of how to fill a multi-processing / multi-threading pool with dependent tasks.
  - [quote.py](./python/quote.py): Add / remove quotes (escapes).