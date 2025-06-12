extern crate proc_macro;
use proc_macro::TokenStream;
use quote::{format_ident, quote};
use syn::{Expr, ItemFn, parse_macro_input};

#[proc_macro_attribute]
pub fn codedefender(attr: TokenStream, item: TokenStream) -> TokenStream {
    let input_fn = parse_macro_input!(item as ItemFn);
    let profile_expr = parse_macro_input!(attr as Expr);

    let profile_str = match profile_expr {
        syn::Expr::Lit(syn::ExprLit {
            lit: syn::Lit::Str(lit),
            ..
        }) => lit.value(),
        _ => panic!("Expected a string literal, e.g. #[codedefender(\"Profile1\")]"),
    };

    let fn_name = &input_fn.sig.ident;
    let upper_name = fn_name.to_string().to_uppercase();
    let struct_name = format_ident!("CDMacroEntry_{}", upper_name);
    let static_ident = format_ident!("CDMACRO_STATIC_{}", upper_name);
    
    let expanded = quote! {
        #[unsafe(no_mangle)]
        #[inline(never)]
        #input_fn

        #[repr(C)]
        struct #struct_name {
            p_func: *const (),
            p_profile: *const u8,
        }
        
        unsafe impl Sync for #struct_name {}

        #[used]
        #[unsafe(link_section = ".cdmacro")]
        static #static_ident: #struct_name = #struct_name {
            p_func: #fn_name as *const (),
            p_profile: concat!(#profile_str, "\0").as_ptr(),
        };
    };

    expanded.into()
}
