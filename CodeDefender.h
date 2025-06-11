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

https://www.youtube.com/watch?v=Fdcw4Mby2RI
*/

#ifndef CODEDEFENDER_H
#define CODEDEFENDER_H
#if defined(_MSC_VER)
#pragma pack(push, 1)
typedef struct CodeDefenderMacro {
  void* pFunc;
  const char* pProfile;
} CodeDefenderMacro;
#pragma pack(pop)
#else
typedef struct __attribute__((packed)) CodeDefenderMacro {
  void* pFunc;
  const char* pProfile;
} CodeDefenderMacro;
#endif

#if defined(__cplusplus)
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif

#if defined(_MSC_VER)
#define CODEDEFENDER_SECTION EXTERN_C __declspec(allocate(".cdmacro"))
#pragma section(".cdmacro", read)

#define CODEDEFENDER_STRINGIFY2(x) #x
#define CODEDEFENDER_STRINGIFY(x) CODEDEFENDER_STRINGIFY2(x)

#define CODEDEFENDER_PRAGMA_LINKER_INCLUDE(symbol) \
  __pragma(comment(linker, "/INCLUDE:" symbol))
#define CODEDEFENDER_SYMBOL_NAME(fn) \
  "_"                                \
  " __cdmacro_entry_" #fn

#define CODEDEFENDER(Profile, ReturnType, Func, Body)                     \
  __declspec(noinline) ReturnType Func Body;                              \
  CODEDEFENDER_SECTION const CodeDefenderMacro __cdmacro_entry_##Func = { \
      (void*)(Func), Profile};                                            \
  CODEDEFENDER_PRAGMA_LINKER_INCLUDE(                                     \
      CODEDEFENDER_STRINGIFY(__cdmacro_entry_##Func));

#elif defined(__GNUC__) || defined(__clang__)
#define CODEDEFENDER_SECTION __attribute__((section(".cdmacro"), used))
#define NOINLINE __attribute__((noinline))

#define CODEDEFENDER(Profile, ReturnType, Func, Body)                        \
  NOINLINE ReturnType Func Body CODEDEFENDER_SECTION const CodeDefenderMacro \
      __cdmacro_entry_##Func = {(void*)(Func), Profile};
#endif
#endif