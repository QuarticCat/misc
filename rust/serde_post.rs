//! An example of how to add post processing into `serde::Deserialize` with
//! minimum code.
//!
//! Key idea: To reuse the default deserialize behaviour, we use `remote`
//! attribute to let it be generated in another namespace.

use serde::{Deserialize, Deserializer};

#[derive(Debug)]
struct Foo {
    foo: i32,
}

impl<'de> Deserialize<'de> for Foo {
    fn deserialize<D: Deserializer<'de>>(deserializer: D) -> Result<Self, D::Error> {
        #[derive(Deserialize)]
        #[serde(remote = "Foo")] // cannot use `Self` here
        struct This {
            foo: i32,
        }

        let mut this = This::deserialize(deserializer)?;
        this.foo += 1; // post process
        Ok(this)
    }
}

fn main() {
    let s = r#"
        {"foo": 0}
    "#;
    println!("{:?}", serde_json::from_str::<Foo>(s).unwrap());
}
