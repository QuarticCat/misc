#!/bin/bash

dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$dir/.."

git config core.hooksPath ||
git config core.hooksPath ./.githooks
