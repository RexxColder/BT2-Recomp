#include "common.h"

s32 func_002C0160(s32 arg0, s32 arg1, s32 arg2);
s32 func_002CF648(s32 arg0, s32 arg1);
s32 func_002CF348(u8 *arg0, s32 arg1, s64 *arg2, s32 *arg3);
void func_002DA3A8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C0238(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void *D_00346E64 __attribute__((section(".data")));

s32 func_002C4590(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4) {
    u8 sp[0xA0];
    s32 v0;
    s32 s1;
    s32 s3;
    s32 s7;
    s32 fp;

    v0 = func_002C0160((s32)arg0, arg1, (s32)sp);
    if (v0 != 0) {
        return v0;
    }
    s1 = *(s32 *)(sp + 0x4);
    s3 = *(s32 *)(sp + 0x0);
    s7 = *(s32 *)(sp + 0x8);
    fp = *(s32 *)(sp + 0x14);
    if (s1 + *(s32 *)(sp + 0xC) < arg3) {
        return 0;
    }

    if (arg1 == 1) {
        if (arg4 >= 0) {
            v0 = func_002CF648((s32)arg0, 1);
            if (v0 != 0) {
                return 0;
            }
            *(s64 *)(sp + 0x20) = (s64)arg4;
            *(s32 *)(sp + 0x28) = s3;
            *(s32 *)(sp + 0x2C) = arg3;
            v0 = func_002CF348(arg0, 1, (s64 *)(sp + 0x20), (s32 *)(sp + 0x40));
            if (v0 != 0) {
                return v0;
            }
        }
        v0 = (s1 < arg3);
    } else if (arg1 == 2) {
        if (D_00346E64 == NULL) {
            v0 = (s1 < arg3);
        } else {
            *(s64 *)(sp + 0x30) = (s64)arg4;
            *(s32 *)(sp + 0x38) = arg3;
            v0 = ((s32 (*)(void *, void *))D_00346E64)(arg0 + 0x12E0, sp + 0x30);
            if (v0 == -1) {
                return 0;
            }
            v0 = (s1 < arg3);
        }
    } else {
        v0 = (s1 < arg3);
    }

    if (v0 != 0) {
        func_002DA3A8(s3, (s32)arg2, s1);
        func_002DA3A8(s7, (s32)(arg2 + s1), arg3 - s1);
    } else {
        func_002DA3A8(s3, (s32)arg2, arg3);
    }
    v0 = func_002C0238((s32)arg0, arg1, arg3, fp);
    if (v0 == 0) {
        v0 = 1;
    }
    return v0;
}
