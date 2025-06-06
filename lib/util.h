#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

#ifndef _STDBOOL_H // Because stdbool just doesnt work for me for some reason ?!?!?!
    #define bool int
    #define true 1
    #define false 0
#endif

#define INFER_PREFIX(x)                                 \
    int x##_push(const void* src, size_t srcsize) {     \
        return push(&x, src, srcsize);                  \
    }                                                   \
                                                        \
    void* x##_get(int h) {                              \
        return get(&x, h);                              \
    }                                                   \
                                                        \
    void x##_write(char* path) {                        \
        write(&x, path);                                \
    }                                                   \
    void x##_clear() {                                  \
        clear(&x);                                      \
    }                                                   \
    int x##_size() {                                    \
        return size(&x);                                \
    }                                                   \

#define INFER_ARG(x, y)                                 \
    int x##_push(const void* src, size_t srcsize) {     \
        return push(&y, src, srcsize);                  \
    }                                                   \
                                                        \
    void* x##_get(int h) {                              \
        return get(&y, h);                              \
    }                                                   \
    void x##_write(char* path) {                        \
        return write(&y, path);                         \
    }                                                   \
    void x##_clear() {                                  \
        clear(&y);                                      \
    }                                                   \
    int x##_size() {                                    \
        return size(&y);                                \
    }                                                   \

#define MEMORY(x)       \
    memory x;           \
    INFER_PREFIX(x)     \

#ifdef DEBUG
#   define DBG(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#   define DBG(fmt, ...)
#endif

#define assert(x, msg) \
    do { if(!(x)) { fprintf(stderr, "%s:%d assertion failed: '%s'\nPanic message:\t%s\n", __FILE__, __LINE__, #x, msg); exit(1); } } while(0)

typedef unsigned char byte;

// shamelessly ripped from a stackexchange thread i lost the link of
// *slightly* tweaked
void hexdump(const void *data, size_t size) {
    const byte *b = (byte *)data;
    size_t i, j;

    size_t colwidth = 4;

    for (i = 0; i < size; i += colwidth) {

        for (j = 0; j < colwidth; j++) {
            if (i + j < size) {
                printf("%2X ", b[i + j]);
            } else {
                printf("   ");
            }

            if (j == 7) {
                printf(" ");
            }
        }

        printf(" |");

        // Print ASCII characters
        for (j = 0; j < colwidth; j++) {
            if (i + j < size) {
                unsigned char c = b[i + j];
                printf("%2c", isprint(c) ? c : '.');
            } else {
                printf(" ");
            }
        }

        printf("\n");
    }
}

#endif // UTIL_H