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
#ifdef __cplusplus
#define CD_EXTERN_C extern "C"
#else
#define CD_EXTERN_C
#endif

// Use this to wrap your function definitions
#define CODEDEFENDER(ReturnType, Func, Scope) \
    CD_EXTERN_C __declspec(noinline) \
    __pragma(comment(linker, "/export:CODEDEFENDER_" #Scope "_" #Func "=" #Func)) \
    ReturnType Func

// Only use this if you want to actually export the function and obfuscate it as well.
#define CODEDEFENDER2(ReturnType, Func, Scope) \
    CD_EXTERN_C __declspec(dllexport) __declspec(noinline) \
    __pragma(comment(linker, "/export:CODEDEFENDER_" #Scope "_" #Func "=" #Func)) \
    ReturnType Func
#endif