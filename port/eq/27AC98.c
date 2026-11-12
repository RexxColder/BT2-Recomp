#include "common.h"

extern f32 D_00387090;
extern f32 D_00387094;
extern f32 D_00387098;

s32 func_0027AC98(s32 arg0, s32 arg1) {
    f32 temp_f8;
    f32 temp_x;
    f32 temp_y;
    s32 stale;

    temp_f8 = *(f32 *)((u8 *)arg0 + 8);
    switch (arg1) {
    case 0:
        if (temp_f8 <= 0.0f) {
            return 0;
        }
        temp_x = *(f32 *)((u8 *)arg0 + 0);
        if ((temp_x >= 2304.0f) || (temp_x <= 1792.0f)) {
            return 0;
        }
        temp_y = *(f32 *)((u8 *)arg0 + 4);
        if (temp_y >= 2272.0f) {
            return 0;
        }
        if (!(temp_y <= 1824.0f)) {
            return 1;
        }
        return 0;
    case 1:
        if (temp_f8 <= 0.0f) {
            return 0;
        }
        temp_x = *(f32 *)((u8 *)arg0 + 0);
        if ((temp_x >= 2368.0f) || (temp_x <= 1728.0f)) {
            return 0;
        }
        temp_y = *(f32 *)((u8 *)arg0 + 4);
        if (D_00387090 <= temp_y) {
            return 0;
        }
        if (!(temp_y <= 1768.0f)) {
            return 1;
        }
        return 0;
    case 2:
        if (temp_f8 <= 0.0f) {
            return 0;
        }
        temp_x = *(f32 *)((u8 *)arg0 + 0);
        if ((D_00387094 <= temp_x) || (temp_x <= 0.0f)) {
            return 0;
        }
        temp_y = *(f32 *)((u8 *)arg0 + 4);
        if (D_00387094 <= temp_y) {
            return 0;
        }
        if (temp_y <= 0.0f) {
            return 0;
        }
        return 1;
    default:
        /* the asm returns the v0 left by the slti/addiu before the jump on these paths */
        stale = (arg1 > 2) ? 2 : 1;
        if (temp_f8 <= 0.0f) {
            return 0;
        }
        temp_x = *(f32 *)((u8 *)arg0 + 0);
        if ((D_00387098 <= temp_x) || (temp_x <= 0.0f)) {
            return stale;
        }
        temp_y = *(f32 *)((u8 *)arg0 + 4);
        if ((D_00387098 <= temp_y) || (temp_y <= 0.0f)) {
            return stale;
        }
        return 1;
    }
}
