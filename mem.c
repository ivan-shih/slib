#include "./mem.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define IsUpper(c)	(((c)>='A')&&((c)<='Z'))
#define IsLower(c)	(((c)>='a')&&((c)<='z'))
#define IsDigit(c)	(((c)>='0')&&((c)<='9'))

void memcpy_s(void *dest, size_t destsz, const void *src, size_t srcsz, size_t copysz) {
    if (dest == src || dest == NULL || src == NULL || destsz < copysz || srcsz < copysz) {
        assert(0);
        return;
    }

    (void) memcpy(dest, src, copysz);
}

void memfill(uint8_t *dest, int val, size_t destsz) {
    if (dest == NULL) {
        assert(0);
        return;
    }

    if (val < 0 || val > UINT8_MAX) {
        assert(0);
        return;
    }

    (void) memset(dest, val, destsz);
}

bool memcmp_s(const void* s1, size_t sz1, const void* s2, size_t sz2, size_t compsz) {
    if (s1 == NULL || s2 == NULL || s1 == s2 || sz1 < compsz || sz2 < compsz) {
        assert(0);
        return false;
    }

    for (size_t i = 0; i < compsz; i++) {
        if (((char*)s1)[i] != ((char*)s2)[i])
            return false;
    }

    return true;
}

void printf_ss(const char* fmt, va_list arp) {
    uint8_t f, r;
    uint32_t i, j, w, v;
    char c, d, str[32], *p;

    for (;;) {
        c = *fmt++;
        if (c == 0) break;			/* End of string */
        if (c != '%') {				/* Non escape character */
            putchar(c);
            continue;
        }
        w = f = 0;
        c = *fmt++;
        if (c == '0') {				/* Flag: '0' padding */
            f = 1; c = *fmt++;
        } else {
            if (c == '-') {			/* Flag: left justified */
                f = 2; c = *fmt++;
            }
        }
        while (IsDigit(c)) {		/* Precision */
            w = w * 10 + c - '0';
            c = *fmt++;
        }
        if (c == 'l' || c == 'L') {	/* Prefix: Size is long int */
            f |= 4; c = *fmt++;
        }
        if (!c) break;
        d = c;
        if (IsLower(d)) d -= 0x20;
        switch (d) {				/* Type is... */
            case 'S' :					/* String */
                p = va_arg(arp, char*);
                for (j = 0; p[j]; j++) ;
                if (!(f & 2)) {
                    while (j++ < w) putchar(' ');
                }
                while (*p) putchar(*p++);
                while (j++ < w) putchar(' ');
                continue;

            case 'C' :					/* Character */
                putchar((char)va_arg(arp, int)); continue;

            case 'B' :					/* Binary */
                r = 2; break;

            case 'O' :					/* Octal */
                r = 8; break;

            case 'D' :					/* Signed decimal */
            case 'U' :					/* Unsigned decimal */
                r = 10; break;

            case 'X' :					/* Hexdecimal */
                r = 16; break;

            default:					/* Unknown type (pass-through) */
                putchar(c); continue;
        }

        /* Get an argument and put it in numeral */
        v = (f & 4) ? (uint32_t)va_arg(arp, long) : ((d == 'D') ? (uint32_t)(long)va_arg(arp, int) : (uint32_t)va_arg(arp, unsigned int));
        if (d == 'D' && (v & 0x80000000)) {
            v = 0 - v;
            f |= 8;
        }
        i = 0;
        do {
            d = (char)(v % r); v /= r;
            if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
            str[i++] = d + '0';
        } while (v && i < sizeof str / sizeof str[0]);
        if (f & 8) str[i++] = '-';
        j = i; d = (f & 1) ? '0' : ' ';
        while (!(f & 2) && j++ < w) putchar(d);
        do {
            putchar(str[--i]);
        } while (i);
        while (j++ < w) putchar(d);
    }
}

void strncpy_s(char* dest, size_t destsz, const char* src, size_t srcsz, size_t copysz) {
    if (dest == NULL || src == NULL || dest == src || destsz < copysz || srcsz < copysz) {
        assert(0);
        return;
    }

    (void) strncpy(dest, src, copysz);
}

void strcpy_s(char* dest, size_t destsz, const char* src, size_t srcsz) {
    if (dest == NULL || src == NULL || dest == src) {
        assert(0);
        return;
    }

    size_t n = strnlen(src, srcsz);

    if (n >= destsz) {
        assert(0);
        return;
    }

    (void) strcpy(dest, src);
}

void strncat_s(char* dest, size_t destsz, const char* src, size_t srcsz) {
    if (dest == NULL || src == NULL || dest == src || destsz < srcsz) {
        assert(0);
        return;
    }

    size_t remaining = destsz - strnlen(dest, destsz);

    if (remaining <= strnlen(src, srcsz)) {
        assert(0);
        return;
    }

    (void) strncat(dest, src, srcsz);
}

int findFirstNot(const uint8_t* data, int len, int targetValue) {
    if (!data) {
        assert(0);
        return -1;
    }

    for (int i = 0; i < len; i++) {
        if (data[i] != targetValue) {
            return i;
        }
    }

    return -1;
}
