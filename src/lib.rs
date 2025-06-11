#![no_std]
#![cfg(target_os = "windows")] // We only support 64bit-PE files for now!
#![doc = include_str!("../README.md")]

#[repr(C, packed)]
pub struct CodeDefenderMacro {
    pub p_func: *const (),
    pub p_profile: *const u8,
}

unsafe impl Sync for CodeDefenderMacro {}
pub use paste::paste;

#[macro_export]
macro_rules! CODEDEFENDER {
    ($profile:expr, fn $name:ident($($arg:ident : $argty:ty),*) -> $ret:ty $body:block) => {
        #[unsafe(no_mangle)]
        #[inline(never)]
        pub extern "C" fn $name($($arg: $argty),*) -> $ret $body

        paste! {
            #[used]
            #[unsafe(link_section = ".cdmacro")]
            static [<CDMACRO_ENTRY_$name:upper>]: codedefender::CodeDefenderMacro = codedefender::CodeDefenderMacro {
                p_func: $name as *const (),
                p_profile: concat!($profile, "\0").as_ptr(),
            };
        }
    };
}
