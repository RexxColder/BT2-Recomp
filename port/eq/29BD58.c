#include "common.h"

extern u8 *D_00387DA0;
extern u8 D_003777A0[] __attribute__((section(".data")));

s32 func_0026EBC0(u8 *arg0, u8 *arg1, s32 *arg2);
void func_0026F118(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
f32 func_0026F148(u8 *arg0, s32 *arg1);
s32 func_002A0EA8(u8 *arg0);
void func_002A1340(void);
void func_002A1590(s32 arg0);
void func_002A15D0(s32 arg0);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_SetShadowOffset(s32 arg0, s32 arg1);
void func_002A15F0(s32 arg0);
void Font_PrintAt(s32 arg0, s32 arg1, u8 *arg2);
void func_002A13E8(void);

void func_0029BD58(void) {
    u8 *p;
    u8 *s0;
    u8 *base;
    s32 tmp[8];
    s32 v;
    f32 f20;
    s32 x;

    p = D_00387DA0;
    if (*(s32 *)(p + 0x4) == 0) {
        return;
    }
    if (*(s32 *)(p + 0x5C) < 0) {
        return;
    }
    s0 = p + 0x8;
    func_0026EBC0(s0, D_003777A0, tmp);
    if (tmp[0] < 0) {
        return;
    }
    func_0026F118(s0, tmp, &tmp[4], &tmp[5]);
    f20 = func_0026F148(s0, tmp);

    p = D_00387DA0;
    base = *(u8 **)(p + 0x4);
    s0 = base + ((*(u32 *)(base + (*(s32 *)(p + 0x5C) * 4)) >> 2) << 2);
    v = func_002A0EA8(s0);
    switch (v) {
        case 1:
            tmp[5] += 0x24;
            break;
        case 2:
            tmp[5] += 0x1C;
            break;
        case 3:
            tmp[5] += 0x14;
            break;
        case 4:
            tmp[5] += 0xC;
            break;
        case 5:
            tmp[5] += 0x4;
            break;
        default:
            break;
    }

    func_002A1340();
    func_002A1590(1);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, (s32)(f20 * 128.0f) & 0xFF);
    func_002A15D0(2);
    Font_SetShadowOffset(1, 2);
    x = (s32)(f20 * 64.0f);
    func_002A15F0((s32)((u32)x << 24) | 0x202020);
    Font_PrintAt(tmp[4], tmp[5], s0);
    func_002A13E8();
}
