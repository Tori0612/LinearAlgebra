#include "base.h"
#include <stdio.h>
#include <string.h>

Arena arena_create(u64 capacity) {
    Arena arena = (Arena)malloc(capacity);
    arena->capacity = capacity;
    arena->pos = ARENA_BASE_POS;

    return arena;
}

void arena_destroy(Arena arena) {
    free(arena);
}

void* arena_push(Arena arena, u64 size, b32 non_zero) {
    u64 pos_aligned = ALIGN_UP_POW2(arena->pos, ARENA_ALIGN);
    u64 new_pos = pos_aligned + size;

    if (new_pos > arena->capacity) { return NULL; }

    arena->pos = new_pos;

    u8* out = (u8*)arena + pos_aligned;

    if (!non_zero) {
        memset(out, 0, size);
    }

    return out;
}

void arena_pop(Arena arena, u64 size) {
    size = MIN(size, arena->pos - ARENA_BASE_POS);
    arena->pos -= size;
}

void arena_pop_to(Arena arena, u64 pos) {
    u64 size = pos < arena->pos ? arena->pos - pos :  0;
    arena_pop(arena, size);
}

void arena_clear(Arena arena) {
    arena_pop_to(arena, ARENA_BASE_POS);
}

void arena_print_usage(Arena arena) {
    u64 used = arena->pos;
    u64 capacity = arena->capacity;
    f32 percent = ((f32)used / (f32)capacity) * 100.0f;

    printf("[Arena Memory] %llu / %llu bytes used (%.2f%%)\n",
            (unsigned long long)used,
            (unsigned long long)capacity,
            percent);
}
