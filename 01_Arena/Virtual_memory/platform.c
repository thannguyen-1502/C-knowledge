#include "platform.h"


uint32_t plat_get_pagesize(void)
{
#ifdef _WIN32
    SYSTEM_INFO sysinfo = { 0 };
    GetSystemInfo(&sysinfo);

    return sysinfo.dwPageSize;
#else
    return (uint32_t)sysconf(_SC_PAGESIZE);
#endif
}

void *plat_mem_reserve(uint64_t size)
{
#ifdef _WIN32
    return VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);
#else
    void * ptr = mmap(NULL, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(ptr == MAP_FAILED)
        return NULL;

    return ptr;
#endif
}


int32_t plat_mem_commit(void *ptr, uint64_t size)
{
#ifdef _WIN32
    void* ret = VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE);
    return ret != NULL;
#else
    int32_t ret = mprotect(ptr, size, PROT_READ | PROT_WRITE);
    return ret == 0;
#endif
}


uint32_t plat_mem_decommit(void *ptr, uint64_t size)
{
#ifdef _WIN32
    return VirtualFree(ptr, size, MEM_DECOMMIT);
#else
    int32_t ret = mprotect(ptr, size, PROT_NONE);
    if (ret != 0) 
        return 0;
    ret = madvise(ptr, size, MADV_DONTNEED);
    return ret == 0;
#endif
}


uint32_t plat_mem_release(void *ptr, uint64_t size)
{
#ifdef _WIN32
    int32_t ret = munmap(ptr, size);
    return ret == 0;
#else
    int32_t ret = munmap(ptr, size);
    return ret == 0;
#endif

}