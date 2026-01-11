#include "arena.h"

int main()
{
    mem_arena* perm_arena = arena_create(KiB(5), KiB(5));

    while (1) {
        arena_push(perm_arena, KiB(1));
        getc(stdin);
    }

    arena_destroy(perm_arena);

    return 0;
}