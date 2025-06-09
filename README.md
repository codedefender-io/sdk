![windows-only](https://img.shields.io/badge/platform-windows-blue)

**⚠️ CodeDefender only supports Windows targets at the moment. ⚠️**

# Rust Software Development

Simply add codedefender to your rust project with the following command:

```sh
cargo add codedefender
```

This will include the rust crate that contains the macro `CODEDEFENDER!`.

```rust
use codedefender::CODEDEFENDER;

fn main() {
  println!("Hello World!");
}

CODEDEFENDER!(main, YourObfuscationProfileHere);
```

# C/C++ Software Development

To use CodeDefender SDK simply include "codedefender.h" into your C/C++ project. Then use the macro provided. 

```c
#include <stdio.h>
#include "CodeDefender.h"

int main(int argc, const char** argv) {
  printf("Hello World!");
}

// Obfuscate 'main' with obfuscation settings in 'Profile1'
CODEDEFENDER(main, Profile1);
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

### Doesnt this macro create unwanted exports?

No. CodeDefender will process your file and remove the exported functions created from the macro from the export directory so that the export directory is not cluttered with unwanted exports.