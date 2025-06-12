![windows-only](https://img.shields.io/badge/platform-windows-blue)

**⚠️ CodeDefender only supports Windows targets at the moment. ⚠️**

# Rust Software Development

Simply add codedefender to your rust project with the following command:

```sh
cargo add codedefender
```

This will include the rust crate that contains the macro `CODEDEFENDER!`.

```rust
use codedefender::*;

#[codedefender("Profile1")]
fn addint(x: i32, y: i32) -> i32 {
    println!("add({}, {})", x, y);
    x + y
}
```

# C/C++ Software Development

To use CodeDefender SDK simply include "codedefender.h" into your C/C++ project. Then use the macro provided. 

```c
#include <stdio.h>
#include "CodeDefender.h"

// You can declare this in your header files!
CODEDEFENDER("Profile1", int, addint, (int a, int b));

int addint(int a, int b) {
  return a + b;
}
```

### Obfuscation Profiles

Profiles are defined within the configuration file created on the SaaS (https://app.codedefender.io). Here is an example of a configuration file exported from the SaaS

```json
{
  "settings": {
    ... // Removed for brevity
  },
  "profiles": [
    {
      "id": "475e59f5-7e01-436f-8406-02600b9b7c64",
      "name": "Profile1", // Here is the profile name!
      "locked": false,
      "settings": {
        // ... Removed for brevity
      },
    }
  ]
}
```

This provides an easy to obfuscate functions with pre-defined obfuscation settings.