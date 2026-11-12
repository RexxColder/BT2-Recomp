#include "m2c_macros.h"

void *memset(void *, s32, u32);
void *func_28BAA8(s32);
void func_003B6C30(void *);

void func_003B7508(void *arg0, u8 *arg1, s32 arg2) {
    s32 size;
    void *r;
    u8 *t;
    s32 i;

    size = arg2 * 188;
    t = arg1;
    memset(arg0, 0, 8);
    r = func_28BAA8(size);
    M2C_FIELD(arg0, void **, 0) = r;
    memset(r, 0, size);
    for (i = 0; i < arg2; i++) {
        M2C_FIELD((u8 *)M2C_FIELD(arg0, u8 **, 0) + i * 188, u8 **, 4) = t;
        t += 0x38;
        func_003B6C30((u8 *)M2C_FIELD(arg0, u8 **, 0) + i * 188);
    }
}
