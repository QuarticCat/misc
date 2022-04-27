//! An example of how to simulate concept before C++20.
//!
//! It imitates the code below:
//!
//! ```
//! template<class T>
//! concept Arithmetic = std::is_arithmetic_v<T>;
//!
//! template<Arithmetic T>
//! void foo(T);
//! ```

#include <type_traits>

template<class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
using Arithmetic = T;

template<class T>
void foo(Arithmetic<T>);
