#pragma once

#ifndef Null
//#ifdef NULL
//    #define Null NULL
//#else
//    #define Null (void*)0
//#endif // NULL
#define Null (void*)0
#define Nullptr Null
#define nil Null
#define Nil Null
#endif // !Null

#ifndef C_API
#define C_API
#endif // !C_API