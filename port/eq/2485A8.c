#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 OldPass_EncodeShort(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00287EE8(void);
extern u8 *D_00387978;

void func_002485A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 buf[7];

    memset(buf, 0, 0x1C);
    buf[0] = arg0;
    buf[1] = arg1;
    buf[2] = arg2;
    buf[3] = arg3;
    buf[4] = 1;
    buf[5] = 1;
    buf[6] = 1;
    if (OldPass_EncodeShort(buf, 1, 1, 1) != 0) {
        *(s32 *)(D_00387978 + 0x40) = func_00287EE8();
    }
}
