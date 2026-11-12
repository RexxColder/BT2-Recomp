#include "common.h"

f32 func_0026F148(u8 *a0, u8 *a1);
void func_0026F118(u8 *a0, u8 *a1, s32 *a2, s32 *a3);
s32 func_002A0EA8(u8 *a0);
void func_002A1340(void);
void Font_SetColorRGBA(s32 a0, s32 a1, s32 a2, s32 a3);
void func_002A15D0(s32 a0);
void Font_SetShadowOffset(s32 a0, s32 a1);
void func_002A15F0(s32 a0);
void Font_PrintAt(s32 x, s32 y, u8 *text);
void func_002A13E8(void);

/* 0x00249FB8: draws one font line from a table entry (arg4 + idx*4 + 4 holds an offset,
 * low two bits cleared). arg5 = index, arg6 = flag (0 or 1 in the caller). */
void func_00249FB8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6) {
    s32 tmp[2];
    f32 f20;
    u32 off;
    s32 r;

    if (arg5 < 0) {
        return;
    }
    if (*(s32 *)arg1 < 0) {
        return;
    }
    func_0026F118(arg0, arg1, &tmp[0], &tmp[1]);
    f20 = func_0026F148(arg0, arg1);
    if (arg6 != 0) {
        tmp[0] += 0x80;
    } else {
        tmp[0] += 0x10;
    }

    off = ((u32)*(s32 *)(arg4 + arg5 * 4 + 4) >> 2) << 2;
    r = func_002A0EA8(arg4 + off);
    if (r == 2) {
        tmp[1] += 0x1C;
    } else if (r < 3) {
        if (r == 1) {
            tmp[1] += 0x24;
        }
    } else {
        if (r == 3) {
            tmp[1] += 0x10;
        } else if (r == 4) {
            tmp[1] += 6;
        }
    }

    func_002A1340();
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, (s32)(f20 * 128.0f) & 0xFF);
    func_002A15D0(2);
    Font_SetShadowOffset(1, 2);
    func_002A15F0((s32)(((u32)(s32)(f20 * 64.0f) << 24) | 0x202020));

    off = ((u32)*(s32 *)(arg4 + arg5 * 4 + 4) >> 2) << 2;
    Font_PrintAt(tmp[0] + arg2, tmp[1] + arg3, arg4 + off);
    func_002A13E8();
}
