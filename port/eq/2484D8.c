#include "common.h"

s32 OldPass_EncodeChar(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00287EE8(void);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387978;
extern u8 *D_00387F2C;

void func_002484D8(u32 arg0, s32 arg1) {
    s32 sp[12];
    u8 *src;
    s32 i;

    if (arg0 < 0x55U) {
        memset(sp, 0, 0x30);
        sp[0] = arg1;
        src = D_00387F2C + (arg0 * 0x22) + 0x1408;
        for (i = 1; i < 8; i++) {
            sp[i] = *(s16 *)src;
            src += 4;
        }
        sp[10] = 1;
        sp[8] = *(s16 *)(D_00387F2C + (arg0 * 0x22) + 0x1426);
        sp[9] = 1;
        sp[11] = 0;
        if (OldPass_EncodeChar(sp, 1, 7, arg0 * 0x10) != 0) {
            *(s32 *)(D_00387978 + 0x40) = func_00287EE8();
        }
    }
}
