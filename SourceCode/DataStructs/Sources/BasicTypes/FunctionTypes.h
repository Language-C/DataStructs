#pragma once

typedef void(*MemFreeFunction)(void*);
typedef void*(*MemMallocFunction)(size_t);

typedef void(*ClassConstructor)(void* const self);
typedef void(*ClassParamConstructor)(void* const self, const void* const params);
typedef void(*ClassCopyConstructor)(void* const dst, const void* const src);

typedef void(*ClassDestructor)(void* const self);
