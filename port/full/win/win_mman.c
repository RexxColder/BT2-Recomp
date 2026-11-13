#include <windows.h>
#include <stddef.h>
void *mmap(void *addr, size_t len, int prot, int flags, int fd, long off) {
    void *p; (void)prot; (void)flags; (void)fd; (void)off;
    p = VirtualAlloc(addr ? addr : (void *)0x30000000u, len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!p && addr) p = VirtualAlloc(NULL, len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    return p ? p : (void *)-1;
}
int munmap(void *addr, size_t len) { (void)len; return VirtualFree(addr, 0, MEM_RELEASE) ? 0 : -1; }
int mprotect(void *addr, size_t len, int prot) { (void)addr; (void)len; (void)prot; return 0; }
