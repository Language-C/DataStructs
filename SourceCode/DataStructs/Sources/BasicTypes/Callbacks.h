#pragma once

typedef void*(*StructDupFunc)(void* self);

// Decl callback function type
typedef void(*NoParamCallback)(void* node);
typedef void(*OneParamCallback)(void* node, void* param);
typedef void(*TwoParamsCallback)(void* node, void* param1, void* param2);
typedef void(*ThreeParamsCallback)(void* node, void* param1, void* param2, void* param3);