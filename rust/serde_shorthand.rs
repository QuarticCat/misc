//! An example of how to add a shorthand for a struct in `serde`. Shorter and
//! cleaner than https://serde.rs/string-or-struct.html.
//!
//! The idea is quite similar to `serde_post.rs`.

use serde::{Deserialize, Deserializer};

#[derive(Debug)]
struct Foo {
    foo: i32,
    others: Option<i32>,
}

impl<'de> Deserialize<'de> for Foo {
    fn deserialize<D: Deserializer<'de>>(deserializer: D) -> Result<Self, D::Error> {
        #[derive(Deserialize)]
        #[serde(remote = "Foo")] // cannot use `Self` here
        struct This {
            foo: i32,
            others: Option<i32>,
        }

        #[derive(Deserialize)]
        #[serde(untagged)]
        enum Helper {
            Short(i32),
            #[serde(with = "This")]
            Full(Foo),
        }

        Ok(match Helper::deserialize(deserializer)? {
            Helper::Short(foo) => Self { foo, others: None },
            Helper::Full(this) => this,
        })
    }
}

fn main() {
    let s = r#"
        123
    "#;
    println!("{:?}", serde_json::from_str::<Foo>(s).unwrap());

    let s = r#"
        {"foo": 1, "others": 2}
    "#;
    println!("{:?}", serde_json::from_str::<Foo>(s).unwrap());
}
