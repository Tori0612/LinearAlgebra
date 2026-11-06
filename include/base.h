#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef size_t sz;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef i8 b8;
typedef i32 b32;

typedef float f32;
typedef double f64;

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

static inline void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

#define ARENA_BASE_POS (sizeof(mem_arena))
#define ARENA_ALIGN (sizeof(void*))
#define ALIGN_UP_POW2(n, p) (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p) -1)))

typedef struct {
    u64 capacity;
    u64 pos;
} mem_arena;

typedef mem_arena* Arena;

Arena arena_create(u64 capacity);
void arena_destroy(Arena arena);
void* arena_push(Arena arena, u64 size, b32 non_zero);
void arena_pop(Arena arena, u64 size);
void arena_pop_to(Arena arena, u64 pos);
void arena_clear(Arena arena);

#define PUSH_STRUCT(arena, T, zero) ((T*)arena_push((arena), sizeof(T), zero))
#define PUSH_ARRAY(arena, T, n, zero) ((T*)arena_push((arena), sizeof(T) * (n), zero))
