#![no_std]
#![cfg(target_os = "windows")] // We only support 64bit-PE files for now!

/// A macro used to mark a function for obfuscation by [CodeDefender.io](https://codedefender.io)
/// using a specific obfuscation profile.
///
/// # Example
///
/// ```
/// use codedefender::CODEDEFENDER;
///
/// fn main() {
///     println!("Hello World!");
/// }
///
/// CODEDEFENDER!(main, YourObfuscationProfileHere);
/// ```
#[macro_export]
macro_rules! CODEDEFENDER {
    ($func:ident, $scope:ident) => {
        const _: () = {
            const EXPORT_STR: &str = concat!(
                "/export:CODEDEFENDER_",
                stringify!($scope),
                "_",
                stringify!($func),
                "=",
                stringify!($func),
                "\0"
            );

            const fn to_array(s: &str) -> &[u8; EXPORT_STR.len()] {
                unsafe { &*(s.as_bytes() as *const [u8] as *const [u8; EXPORT_STR.len()]) }
            }

            #[used]
            #[link_section = ".drectve"]
            static _CODEDEFENDER_EXPORT: [u8; EXPORT_STR.len()] = *to_array(EXPORT_STR);
        };
    };
}
