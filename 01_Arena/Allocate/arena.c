#include "arena.h"


mem_arena * arena_create(u64 capacity)
{
    mem_arena *arena = (mem_arena*)(malloc(capacity));
    if(arena == NULL)
        arena_error("Can not allocate arena memory");
    arena->capacity = capacity;
    arena->pos = ARENA_BASE_POS;
    return arena;
}
void arena_destroy(mem_arena *arena)
{
    if(arena == NULL)
        arena_error("Arena memory is null");

    free(arena);
}

void *arena_push(mem_arena *arena, u64 size)
{
    u64 align_pos = ALIGN_UP_POW2(arena->pos, ARENA_DEFAUL_ALIGN);  /*Làm tròn địa chỉ cấp phát tiếp theo*/
    u64 new_pos =  align_pos + size;
    if( new_pos > arena->capacity)
        arena_error("Arena memory is full");
        
    arena->pos = new_pos;
    u8 *out = (u8*)(arena) + align_pos;
    memset(out, 0, size);
    return out;
}


void arena_pop(mem_arena *arena, u64 size)
{
    size = MIN(size, arena->pos - ARENA_BASE_POS);
    arena->pos -= size;
}

void arena_pop_to(mem_arena *arena, u64 pos)
{
    u64 size = pos < arena->pos ? arena->pos - pos: 0;
    arena_pop(arena, size);
}

void arena_clear(mem_arena *arena)
{
    arena_pop_to(arena, ARENA_BASE_POS);
}

void arena_error(char *message)
{
    printf("%s\n", message);
    while(1);
}

