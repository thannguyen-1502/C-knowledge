#include "arena.h"
#include "platform.h"


mem_arena * arena_create(u64 reserve_size, u64 commit_size)
{
    u32 pagesize = plat_get_pagesize();

    reserve_size = ALIGN_UP_POW2(reserve_size, pagesize);
    commit_size = ALIGN_UP_POW2(commit_size, pagesize);

    mem_arena* arena = (mem_arena*)plat_mem_reserve(reserve_size);
    if(arena == NULL)
        arena_error("Can not reserve memory");

    if (!plat_mem_commit(arena, commit_size)) {
        arena_error("Can not commit memory");
    }

    arena->reserve_size = reserve_size;
    arena->commit_size = commit_size;
    arena->pos = ARENA_BASE_POS;
    arena->commit_pos = commit_size;
    
    return arena;
}
void arena_destroy(mem_arena *arena)
{
    plat_mem_release(arena, arena->reserve_size);
}

void *arena_push(mem_arena *arena, u64 size)
{
    u64 pos_aligned = ALIGN_UP_POW2(arena->pos, ARENA_DEFAUL_ALIGN);  /*Làm tròn địa chỉ cấp phát tiếp theo*/
    u64 new_pos =  pos_aligned + size;
    if( new_pos > arena->reserve_size)
        arena_error("Arena memory is full");
        
    if(new_pos > arena->commit_size)
    {
        u64 new_commit_pos = new_pos;
        /* ALIN commit pos  (n + p - 1) & ~(p - 1)*/
        /* new_commit_pos = (new_commit_pos + commit_size - 1) & ~(commit_size - 1) */
        new_commit_pos += arena->reserve_size - 1;
        new_commit_pos -= new_commit_pos%arena->commit_size;
        new_commit_pos = MIN(new_commit_pos, arena->reserve_size);

        u8 *mem = (u8*)arena + arena->commit_pos;
        u64 commit_size = new_commit_pos - arena->commit_pos;

        if(!plat_mem_commit(mem, commit_size))
            arena_error("Can not commit additional mem");

        arena->commit_pos = new_commit_pos;
    }

    u8 *out = (u8*)arena + pos_aligned;
    arena->pos = new_pos;

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

