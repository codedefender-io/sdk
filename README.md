![windows-only](https://img.shields.io/badge/platform-windows-blue)

**⚠️ CodeDefender only supports Windows targets at the moment. ⚠️**

# Rust Software Development

Simply add codedefender to your rust project with the following command:

```sh
cargo add codedefender
```

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

# MASM Software Development

```MASM
include codedefender.inc
EXTERN MessageBoxA : PROC

.data
caption     db "Hello", 0
message     db "This is MyFunc (64-bit)!", 0

.code
PUBLIC MyFunc
MyFunc PROC
    sub     rsp, 28h             ; shadow space + alignment
    mov     rcx, 0               ; hWnd = NULL
    lea     rdx, message         ; LPCSTR lpText
    lea     r8,  caption         ; LPCSTR lpCaption
    mov     r9, 0                ; uType = MB_OK
    call    MessageBoxA
    add     rsp, 28h
    ret
MyFunc ENDP

; Use the macro from the included file
CODEDEFENDER "Profile1", MyFunc
END
```

### Obfuscation Profiles

Profiles are defined within the configuration file created on the SaaS (https://app.codedefender.io). Here is an example of a configuration file exported from the SaaS

```yaml
version: "1.0.0"
module_settings:
  ida_crasher: false
  import_protection: false
  fake_pdb_string:
    enabled: false
    value: ""
  custom_section_name:
    enabled: false
    value: ""
profiles:
  - name: "Profile1"
    passes: # Assign your obfuscation passes here
      - type: ObscureReferences
      - type: ObscureConstants
    compiler_settings:
      assembler_settings:
        shuffle_basic_blocks: false
        instruction_prefix: ""
        random_prefix_chance: 0
      optimization_settings:
        constant_propagation: true
        instruction_combine: true
        dead_code_elim: true
        prune_useless_block_params: true
        iterations: 0
      lifter_settings:
        lift_calls: true
        max_stack_copy_size: 1024
        split_on_calls_fallback: true
    symbols:
      - !Name "main" # Specify a symbol by name
      - !Rva 0x1000  # Specify a symbol by RVA
```

This provides an easy to obfuscate functions with pre-defined obfuscation settings.
