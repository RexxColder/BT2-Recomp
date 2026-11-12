#include "common.h"

extern u8 gGfxLens[];
extern s32 gBtlCam;
s32 Dma_BeginDirect(void);
s32 Dma_EndDirect(void *arg0);
s32 func_002865F0(s32 arg0, s32 arg1, s32 arg2);
void func_00271370(void);
void func_0025BF08(s32 arg0);
void func_0025C058(void);
s32 func_00284058(s32 arg0, s32 arg1, s32 arg2);
s32 Tex_Log2Size(s32 arg0);
s32 func_00283D38(s32 arg0, s32 arg1, s32 arg2);

s32 func_00284530(s32 arg0, s32 arg1) {
    s32 flag;
    s32 i;
    s32 base;
    s32 v11;
    s32 log2a;
    s32 log2b;
    u64 *q;
    u64 *q10;

    flag = arg0 & 0xFF;

    i = 0;
    if (*(s32 *)(gGfxLens + 0x10) == 0) {
        for (i = 1; i < 8; i++) {
            if (*(s32 *)(gGfxLens + 0x10 + 48 * i) != 0) {
                break;
            }
        }
    }
    if (i == 8) {
        return 8;
    }

    func_002865F0(*(s32 *)(gGfxLens + 0x180), 0x2F00, 0x2E00);
    func_00271370();
    if (flag != 0) {
        func_0025BF08(arg1);
        func_0025C058();
    }

    v11 = *(s32 *)(*(s32 *)(gGfxLens + 0x180) + 0x10);
    base = Dma_BeginDirect();
    q = (u64 *)func_00284058(base, flag, arg1);

    q[0] = 0x100000000000800AULL;
    q[1] = 14;
    q[2] = 84;
    q[3] = 66;
    q[4] = 74;
    q[5] = 67;
    q[6] = 0;
    q[7] = 74;
    q[8] = 0;
    q[9] = 75;
    q[10] = 0x2000C;
    q[11] = 71;
    q[12] = 0x2000C;
    q[13] = 72;
    q[14] = 5;
    q[15] = 8;
    q[16] = 5;
    q[17] = 9;

    log2a = Tex_Log2Size(256);
    log2b = Tex_Log2Size(256);
    q[18] = ((u64)log2a << 26) | ((u64)log2b << 30) | 0x12A00ULL;
    q[19] = 6;

    q10 = q + 20;
    q10[0] = *(u64 *)((u8 *)v11 + 0x30) | 0x0005C00400002F00ULL;
    q10[1] = 7;
    Dma_EndDirect((void *)(q10 + 2));

    return func_00283D38(*(s32 *)((u8 *)gBtlCam + 0x600), flag, arg1);
}
