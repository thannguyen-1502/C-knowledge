#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#ifdef _WIN32
#include <windows.h>
#else
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <sys/mman.h>
#endif
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

uint32_t plat_get_pagesize(void);
void *plat_mem_reserve(uint64_t size);
int32_t plat_mem_commit(void *ptr, uint64_t size);
uint32_t plat_mem_decommit(void *ptr, uint64_t size);
uint32_t plat_mem_release(void *ptr, uint64_t size);
#endif