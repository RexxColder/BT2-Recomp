#include "common.h"

extern void func_002EF200(s32 arg0);

/* 0x001006D8: calls 0x002EF200(0) and returns 0. The original issues a sync after the call (a memory barrier, a
 * no-op for this single-threaded port). */
s32 func_001006D8(void) {
    func_002EF200(0);
    return 0;
}
