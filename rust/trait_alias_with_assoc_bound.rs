//! An example of how to implement trait aliases with associated type bounds.
//!
//! Ref: https://rust-lang.github.io/rfcs/2089-implied-bounds.html#traits

use std::{fmt::Display, str::FromStr};

// // This one doesn't work!
//
// pub trait AliasTrait: FromStr where Self::Err: Display {}
//
// impl<T: FromStr<Err = impl Display>> AliasTrait for T {}

pub trait AliasTrait: FromStr<Err = <Self as AliasTrait>::Err> {
    type Err: Display;
}

impl<T: FromStr<Err = impl Display>> AliasTrait for T {
    type Err = T::Err;
}

pub fn with_alias<T: AliasTrait>() -> T {
    T::from_str("123").map_err(|e| println!("{e}")).unwrap()
}

pub fn without_alias<T: FromStr<Err = impl Display>>() -> T {
    T::from_str("123").map_err(|e| println!("{e}")).unwrap()
}
