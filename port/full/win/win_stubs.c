#include <stddef.h>
#include <stdio.h>
#undef stderr
FILE *stderr;   /* el C del juego referencia `stderr` como variable (Linux); en mingw es una macro */
int backtrace(void **b, int n) { (void)b; (void)n; return 0; }
void backtrace_symbols_fd(void *const *b, int n, int fd) { (void)b; (void)n; (void)fd; }
int dladdr(const void *a, void *info) { (void)a; (void)info; return 0; }
void bt2_trace_dump(const char *why) { (void)why; }
void bt2_init_stderr(void) { if (!stderr) stderr = _fdopen(2, "w"); }
