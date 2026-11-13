#ifndef WIN_EXECINFO_H
#define WIN_EXECINFO_H
int backtrace(void **buffer, int size);
void backtrace_symbols_fd(void *const *buffer, int size, int fd);
#endif
