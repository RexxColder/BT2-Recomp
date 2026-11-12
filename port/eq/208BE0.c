#include "common.h"

extern s32 D_00387930;
extern s32 D_00387E18;
extern f32 D_00385960;
u8 *func_00211288(s32 idx);
u8 *BtlChar_GetPos(u8 *ch);
u8 *func_002B1DD0(s32 idx);
void sceVu0Normalize(u8 *dst, u8 *src);
void func_00312680(f32 s, u8 *dst, u8 *src);
void func_003126C8(u8 *dst, u8 *src);
f32 func_0029DFD0(u8 *v);
extern s32 func_00209018(s32 idx, u8 *dst, s32 flag);

/* 0x00208BE0: (idx, dst) writes a direction vector for slot idx into dst (copy of a char position, a table
 * normalize, or a computed vector re-scaled to unit length when longer than D_00385960). */
void func_00208BE0(s32 idx, u8 *dst) {
    f32 len;

    if (D_00387930 != 0 && (u32)idx < 2) {
        func_003126C8(dst, BtlChar_GetPos(func_00211288(idx)) + 0x30);
        return;
    }
    if (D_00387E18 != 0 && (u32)idx < 3) {
        sceVu0Normalize(dst, func_002B1DD0(idx) + 0x130);
        return;
    }
    func_00209018(idx, dst, 0);
    len = func_0029DFD0(dst);
    if (D_00385960 < len) {
        func_00312680(1.0f / len, dst, dst);
    }
}
