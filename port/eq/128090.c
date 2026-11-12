#include "common.h"

extern f32 D_00384150;
extern f32 D_00384154;

/* 0x00128090: f0 = 1.0f. When the pointer at arg0+0x64 is set, f0 = D_00384150 and the word at (*(arg0+0x64)+0x20)
 * selects a jump-table case (idx = word - 0x36, valid when unsigned idx < 0x11A). The 39 listed cases set
 * f0 = D_00384154; the others leave it. Then f0 = 0.5f when the word at arg0+0x68 is nonzero. */
f32 func_00128090(u8 *arg0) {
    f32 f0 = 1.0f;
    u8 *obj;
    s32 idx;

    if (*(s32 *)(arg0 + 0x64) != 0) {
        f0 = D_00384150;
        obj = (u8 *)*(s32 *)((u8 *)*(s32 *)(arg0 + 0x64) + 0x20);
        idx = *(s32 *)obj - 0x36;
        if ((u32)idx < 0x11A) {
            switch (idx) {
                case 0: case 1: case 2: case 4: case 7:
                case 19: case 20: case 21: case 22: case 23: case 24: case 25: case 26:
                case 65: case 69: case 70: case 71: case 81: case 83: case 88: case 89:
                case 126: case 127: case 131: case 171: case 176: case 214: case 220:
                case 260: case 263: case 264: case 267: case 268: case 269: case 271:
                case 272: case 274: case 275: case 281:
                    f0 = D_00384154;
                    break;
                default:
                    break;
            }
        }
    }
    if (*(s32 *)(arg0 + 0x68) != 0) {
        f0 = 0.5f;
    }
    return f0;
}
