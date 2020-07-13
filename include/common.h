#pragma once
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <iostream>
#ifdef UTF16_MeyaS
    #define Char_MeyaS wchar_t
    #define String_MeyaS std::wstring
    #define cout_MeyaS std::wcout
    #define CPMeyaS(literal) WIDEN(literal)
    #define WIDEN(literal) L##literal
#else
    #define Char_MeyaS char
    #define String_MeyaS std::string
    #define cout_MeyaS std::wcout
    #define CPMeyaS(literal) literal
#endif
namespace MeyaS {
    typedef unsigned int uint;
}