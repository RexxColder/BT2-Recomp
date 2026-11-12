#include "common.h"

extern f32 D_003874EC;
extern f32 D_003874F0;
extern f32 D_003874F4;
extern f32 D_003874F8;
extern f32 D_003874FC;
extern f32 D_00387500;
extern f32 D_00387504;
extern f32 D_00387508;
extern f32 D_0038750C;
extern f32 D_00387510;
extern f32 D_00387514;
extern f32 D_00387518;
extern f32 D_0038751C;
extern f32 D_00387520;

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atan2f(f32 y, f32 x);
u8 *func_002B1DD0(s32 arg0);
s32 func_002ADFC8(u8 *arg0);
s32 func_002ADFD0(u8 *arg0);
void func_00312650(void *arg0, void *arg1, void *arg2);

void func_002B0480(u8 *self) {
    u8 sp[0x30];
    f32 *src = (f32 *)sp;
    f32 *diff = (f32 *)(sp + 0x10);
    f32 *dir = (f32 *)(sp + 0x20);
    u32 *flags = (u32 *)(self + 0xB0);
    u8 *target = func_002B1DD0(0);
    f32 limit = D_003874EC;
    f32 ang;
    f32 reach;
    f32 dist;
    f32 side;
    f32 turn;
    f32 base;
    f32 v;

    if ((u32)(*(s32 *)(self + 0x10) - 1) >= 2) {
        return;
    }
    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 0;
    flags[3] = 0;
    flags[4] = 0;
    *(f32 *)(self + 0x16C) = 1.0f;
    dir[0] = sinf(*(f32 *)(target + 0x15C));
    dir[1] = 0.0f;
    dir[2] = cosf(*(f32 *)(target + 0x15C));
    if (*(s32 *)(self + 0x10) == 1) {
        ang = *(f32 *)(target + 0x15C) + D_003874F0;
    } else {
        ang = *(f32 *)(target + 0x15C) + D_003874F4;
    }
    reach = 15.0f;
    if (func_002ADFC8(self) == 3) {
        reach = 20.0f;
    }
    base = *(f32 *)(target + 0xD0) + dir[0] * 100.0f;
    src[0] = base + sinf(ang) * reach;
    src[1] = *(f32 *)(target + 0xD4) + dir[1] * 100.0f;
    base = *(f32 *)(target + 0xD8) + dir[2] * 100.0f;
    src[2] = base + cosf(ang) * reach;
    func_00312650(diff, src, self + 0xD0);

    v = diff[0];
    if (v < -limit) {
        v = v + D_003874F8;
        diff[0] = v;
    }
    if (limit < v) {
        v = v - D_003874FC;
        diff[0] = v;
    }
    base = diff[2];
    if (base < -limit) {
        base = base + D_00387500;
        diff[2] = base;
    }
    if (limit < base) {
        base = base - D_00387504;
        diff[2] = base;
    }
    dist = __builtin_sqrtf(__builtin_fabsf(v * v + base * base));
    side = diff[1];
    if (func_002ADFC8(target) == 7) {
        side = 0.0f;
    }
    v = diff[0];
    if (D_00387508 < __builtin_fabsf(v) || D_00387508 < __builtin_fabsf(diff[2])) {
        turn = atan2f(v, diff[2]);
        v = diff[0];
        base = diff[2];
    } else {
        turn = 0.0f;
        base = diff[2];
    }
    ang = turn - *(f32 *)(self + 0x70);
    if (ang < D_0038750C) {
        ang = ang + D_00387510;
    }
    if (D_00387514 < ang) {
        ang = ang - D_00387518;
    }
    dist = dist - 100.0f;
    reach = ((v * dir[0] + base * dir[2]) - 100.0f) / 100.0f + D_0038751C;
    *(f32 *)(self + 0x16C) = reach;
    if (reach < D_00387520) {
        *(f32 *)(self + 0x16C) = D_00387520;
    }
    if (2.0f < *(f32 *)(self + 0x16C)) {
        *(f32 *)(self + 0x16C) = 2.0f;
    }

    switch (func_002ADFC8(self)) {
    case 1:
        if (func_002ADFC8(target) != 7) {
            if (20.0f < dist) {
                *(f32 *)&flags[1] = sinf(ang);
                *(f32 *)&flags[2] = -cosf(ang);
            }
            if (side < -10.0f) {
                flags[0] |= 0x800;
            }
            if (10.0f < side) {
                flags[0] |= 0x200;
            }
        } else if (*(s32 *)(self + 4) * 5 < func_002ADFD0(target)) {
            flags[0] |= 0x4000;
        }
        break;
    case 2:
        if (func_002ADFC8(target) != 7) {
            if (0.0f < dist) {
                *(f32 *)&flags[1] = sinf(ang);
                *(f32 *)&flags[2] = -cosf(ang);
            }
            if (60.0f < dist) {
                flags[0] |= 0x100;
            }
            if (side < -10.0f) {
                flags[0] |= 0x800;
            }
            if (10.0f < side) {
                flags[0] |= 0x200;
            }
        } else if (*(s32 *)(self + 4) * 5 < func_002ADFD0(target)) {
            flags[0] |= 0x4000;
        }
        break;
    case 3:
        if (0.0f < dist) {
            *(f32 *)&flags[1] = sinf(ang);
            v = cosf(ang);
            flags[0] |= 0x100;
            *(f32 *)&flags[2] = -v;
        }
        if (side < -10.0f) {
            flags[0] |= 0x800;
        }
        if (10.0f < side) {
            flags[0] |= 0x200;
        }
        break;
    case 4:
    case 5:
        if (10.0f < dist) {
            *(f32 *)&flags[1] = sinf(ang);
            *(f32 *)&flags[2] = -cosf(ang);
        }
        if (side < -10.0f) {
            flags[0] |= 0x800;
        }
        if (10.0f < side) {
            flags[0] |= 0x200;
        }
        break;
    default:
        break;
    }
}
