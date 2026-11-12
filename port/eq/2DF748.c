#include "common.h"

s32 func_002DF838(void *arg0, s32 arg1, s32 arg2);
void func_002DFBC8(void *arg0);
void func_003061A8(void *arg0, s32 arg1, void *arg2, void *arg3);

s32 func_002DF748(void *arg0, void **arg1) {
    s32 sp[4];
    u8 *temp_s3;
    u8 *vt;
    void (*fn)(void *, s32, s32, void *);
    void (*fn2)(void *, s32, void *);
    void (*fn3)(void *, s32, void *);
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s4;

    temp_s3 = (u8 *)arg0 + 0x38C;
    vt = *(u8 **)arg1;
    fn = *(void (**)(void *, s32, s32, void *))(vt + 0x18);
    fn(arg1, 1, 0x7FFFFFFF, temp_s3);
    temp_a1 = *(s32 *)((u8 *)arg0 + 0x38C);
    temp_s0 = temp_a1 & ~3;
    temp_s4 = func_002DF838(arg0, temp_a1, *(s32 *)((u8 *)arg0 + 0x390));
    func_003061A8(temp_s3,
                  ((temp_s0 + 8 + ((s32)((temp_a1 - temp_s0) * 8) >> 3)) - 4) - *(s32 *)((u8 *)arg0 + 0x38C),
                  temp_s3, sp);
    vt = *(u8 **)arg1;
    fn2 = *(void (**)(void *, s32, void *))(vt + 0x20);
    fn2(arg1, 0, temp_s3);
    vt = *(u8 **)arg1;
    fn3 = *(void (**)(void *, s32, void *))(vt + 0x1C);
    fn3(arg1, 1, sp);
    func_002DFBC8(arg1);
    return temp_s4;
}
