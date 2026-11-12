#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_003854EC;
extern f32 D_003854F0;

void func_001D6C30(u8 *obj) {
    u8 *g;
    f32 timer;
    f32 divisor;
    f32 pos_a;
    f32 pos_b;
    f32 vel_a;
    f32 vel_b;
    f32 lim_a;
    f32 lim_b;
    u8 flags;
    s32 reached;

    switch (obj[0x47]) {
    case 0:
        obj[0x4B] = 0;
        obj[0x4C] = 0;
        g = D_00387E9C;
        *(s32 *)(g + 0x143C) -= 1;
        break;

    case 1:
        timer = *(f32 *)(obj + 0x3C) - 1.0f;
        *(f32 *)(obj + 0x3C) = timer;
        if (!(timer <= 0.0f)) {
            break;
        }
        *(f32 *)(obj + 0x3C) = 0.0f;
        obj[0x4C] = 1;
        obj[0x47] = obj[0x47] + 1;
        /* fall through */

    case 2:
        obj[0x48] = obj[0x48] | 4;
        *(f32 *)(obj + 0x2C) = 128.0f;
        *(f32 *)(obj + 0x24) = D_003854EC;
        *(f32 *)(obj + 0x28) = 120.0f;
        obj[0x47] = obj[0x47] + 1;
        *(s32 *)(obj + 0x20) = 0;
        break;

    case 3:
        if (obj[0x48] != 0) {
            break;
        }
        divisor = D_003854F0;
        pos_a = 150.0f - *(f32 *)(obj + 0x20);
        pos_b = 0.0f - *(f32 *)(obj + 0x2C);
        *(f32 *)(obj + 0x28) = 150.0f;
        *(f32 *)(obj + 0x34) = 0.0f;
        obj[0x48] = 6;
        obj[0x47] = obj[0x47] + 1;
        *(f32 *)(obj + 0x24) = pos_a / divisor;
        *(f32 *)(obj + 0x30) = pos_b / divisor;
        break;

    case 4:
        if (obj[0x48] == 0) {
            obj[0x47] = 0;
        }
        break;

    default:
        break;
    }

    if (obj[0x4C] == 0) {
        return;
    }

    flags = obj[0x48];
    if (flags & 2) {
        vel_b = *(f32 *)(obj + 0x30);
        pos_b = *(f32 *)(obj + 0x2C) + vel_b;
        *(f32 *)(obj + 0x2C) = pos_b;
        lim_b = *(f32 *)(obj + 0x34);
        if (vel_b > 0.0f) {
            reached = (lim_b < pos_b);
        } else {
            reached = (pos_b < lim_b);
        }
        if (reached) {
            *(f32 *)(obj + 0x2C) = lim_b;
            flags = flags & 0xFD;
            obj[0x48] = flags;
        }
    }

    if (flags & 4) {
        vel_a = *(f32 *)(obj + 0x24);
        pos_a = *(f32 *)(obj + 0x20) + vel_a;
        *(f32 *)(obj + 0x20) = pos_a;
        lim_a = *(f32 *)(obj + 0x28);
        if (vel_a > 0.0f) {
            reached = (lim_a < pos_a);
        } else {
            reached = (pos_a < lim_a);
        }
        if (reached) {
            *(f32 *)(obj + 0x20) = lim_a;
            obj[0x48] = flags & 0xFB;
        }
    }
}
