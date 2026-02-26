# branchless

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Language: C](https://img.shields.io/badge/Language-C11-green.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Header-only](https://img.shields.io/badge/Header--only-yes-brightgreen.svg)](branchless.h)

A single-header C library providing branchless bit manipulation functions for high-performance computing.

## Features

- Header-only library - just include and use
- No dependencies (only standard C headers)
- C11 compliant
- 32-bit and 64-bit integer support

## Installation

Copy `branchless.h` to your project directory and include it:

```c
#define BRANCHLESS_IMPLEMENTATION
#include "branchless.h"
```

> **Note:** Define `BRANCHLESS_IMPLEMENTATION` in exactly one source file before including the header.

## API Reference

### Sign Functions

| Function | Description |
|----------|-------------|
| `positive_sign(x)` | Returns 1 for positive/zero, 0 for negative |
| `negative_sign(x)` | Returns 0 for positive/zero, -1 for negative |
| `sign_sign(x)` | Returns 1 for positive/zero, -1 for negative |
| `sign_sign_zero(x)` | Returns 1 for positive, -1 for negative, 0 for zero |

### Utility Functions

| Function | Description |
|----------|-------------|
| `is_power_of_2_int32(x)` / `is_power_of_2_int64(x)` | Check if value is a power of 2 |
| `opposite_sign_int32(x, y)` / `opposite_sign_int64(x, y)` | Check if values have opposite signs |
| `abs_int32(x)` / `abs_int64(x)` | Compute absolute value |
| `min_int32(x, y)` / `min_int64(x, y)` | Return minimum of two values |
| `max_int32(x, y)` / `max_int64(x, y)` | Return maximum of two values |
| `count_bits_int32(x)` / `count_bits_int64(x)` | Count set bits (population count) |

## Building Tests

```bash
mkdir build && cd build
cmake ..
make
./AllTests
```

## References

- [Bit Twiddling Hacks](http://graphics.stanford.edu/~seander/bithacks.html) by Sean Eron Anderson
- [Bit Tricks](http://www.coranac.com/documents/bittrick/) by cearn

## License

MIT License - Copyright (c) 2025 Alexander Zhipa

See [LICENSE](LICENSE) for details.
