#include "arena.h"

int main()
{
    mem_arena *arena = arena_create(KiB(1));

    u64 ptr_size = 10;

    u8 *ptr = (u8*)arena_push(arena, ptr_size);

    for (size_t i = 0; i < ptr_size; i++)
    {
        ptr[i] = i;
        printf("%d ", ptr[i]);
    }
    
    arena_destroy(arena);
    return 0;
}