/* MIT License

Copyright (c) 2025 Back Engineering Labs, Inc

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
*/

#ifndef CODEDEFENDER_H
#define CODEDEFENDER_H
#if defined(__cplusplus)
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif

#if defined(_MSC_VER)
#define CODEDEFENDER_NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#define CODEDEFENDER_NOINLINE __attribute__((noinline))
#else
#define CODEDEFENDER_NOINLINE
#endif

#if defined(_MSC_VER)
#define CODEDEFENDER_SECTION EXTERN_C __declspec(allocate(".cdmacro"))
#pragma section(".cdmacro", read)

#define CODEDEFENDER_STRINGIFY2(x) #x
#define CODEDEFENDER_STRINGIFY(x) CODEDEFENDER_STRINGIFY2(x)

#define CODEDEFENDER_PRAGMA_LINKER_INCLUDE(symbol) \
  __pragma(comment(linker, "/INCLUDE:" #symbol))
#define CODEDEFENDER_SYMBOL_NAME(fn) \
  "_"                                \
  " __cdmacro_entry_" #fn

// https://www.youtube.com/watch?v=ss142Aix2Bo
#define CODEDEFENDER(Profile, ReturnTy, Func, Params)                        \
  CODEDEFENDER_NOINLINE ReturnTy Func Params;                                \
  __pragma(pack(push, 1)) __declspec(align(1)) CODEDEFENDER_SECTION struct { \
    void* pFunc;                                                             \
    char str[sizeof(Profile)];                                               \
  } __cdmacro_entry_##Func = {(void*)Func, Profile};                         \
  __pragma(pack(pop)) CODEDEFENDER_PRAGMA_LINKER_INCLUDE(__cdmacro_entry_##Func)

#elif defined(__GNUC__) || defined(__clang__)
#define CODEDEFENDER_SECTION __attribute__((section(".cdmacro"), used))
// https://www.youtube.com/watch?v=ss142Aix2Bo
#define CODEDEFENDER(Profile, ReturnTy, Func, Params) \
  CODEDEFENDER_NOINLINE ReturnTy Func Params;         \
  CODEDEFENDER_SECTION const struct {                 \
    void* pFunc;                                      \
    char str[sizeof(Profile)];                        \
  } __cdmacro_entry_##Func = {(void*)Func, Profile};  \
  CODEDEFENDER_PRAGMA_LINKER_INCLUDE(__cdmacro_entry_##Func)
#endif
#endif