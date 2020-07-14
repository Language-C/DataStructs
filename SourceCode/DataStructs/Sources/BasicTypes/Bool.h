#pragma once

#ifdef __cplusplus
using Bool = bool;
#define False false
#define True  true
#else
typedef enum Bool_
{
    False = 0,
    True,
} Bool;
#endif // __cplusplus

typedef struct NullBool
{
    Bool Value;
    Bool Valid;
} NullBool;