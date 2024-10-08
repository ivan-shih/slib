#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void memcpy_s(void *dest, size_t destsz, const void *src, size_t srcsz, size_t copysz);
void memfill(uint8_t *dest, int val, size_t destsz);
bool memcmp_s(const void* s1, size_t sz1, const void* s2, size_t sz2, size_t compsz);
void printf_ss(const char* fmt, va_list arp);
void strncpy_s(char* dest, size_t destsz, const char* src, size_t srcsz, size_t copysz);
void strcpy_s(char* dest, size_t destsz, const char* src, size_t srcsz);
void strncat_s(char* dest, size_t destsz, const char* src, size_t srcsz);
int findFirstNot(const uint8_t* data, int len, int targetValue);

#ifdef __cplusplus
}
#endif
