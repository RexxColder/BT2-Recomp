#ifndef WIN_DLFCN_H
#define WIN_DLFCN_H
typedef struct { const char *dli_fname; void *dli_fbase; const char *dli_sname; void *dli_saddr; } Dl_info;
int dladdr(const void *addr, Dl_info *info);
#endif
