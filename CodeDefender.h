#ifndef CODEDEFENDER_H
#define CODEDEFENDER_H
#define CODEDEFENDER(Func, Scope) \
    __pragma(comment(linker, "/export:CODEDEFENDER_" #Scope "_" #Func "=" #Func))
#endif