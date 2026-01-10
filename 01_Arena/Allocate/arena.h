#ifndef __ARENA_H__
#define __ARENA_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

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

#define KiB(n)((u64)(n << 10))  /* n*2^10 */
#define MiB(n)((u64)(n << 20))  /* n*2^20 */
#define GiB(n)((u64)(n << 30))  /* n*2^30 */

#define MIN(a, b)(((a) < (b)) ? (a) : (b))
#define MAX(a, b)(((a) > (b)) ? (a) : (b))

#define ALIGN_UP_POW2(n, p) (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p)-1)))
#define ARENA_BASE_POS (sizeof(mem_arena))
#define ARENA_DEFAUL_ALIGN (sizeof(void*))

#define PUSH_STRUCT(arena, T)(T*)(arena_push(arena, sizeof(T)));
#define PUSH_STRUCT_ARRAY(arena, T, n)(T*)(arena_push(arena, sizeof(T)*n));

typedef struct
{
    u64 capacity;
    u64 pos;
} mem_arena;

mem_arena * arena_create(u64 capacity);
void arena_destroy(mem_arena * arena);
void *arena_push(mem_arena *arena, u64 size);
void arena_pop(mem_arena *arena, u64 size);
void arena_pop_to(mem_arena *arena, u64 pos);
void arena_clear(mem_arena *arena);
void arena_error(char *message);
#endif