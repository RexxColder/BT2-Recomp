#include "common.h"

extern u8 *D_0042A580 __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));
extern u8 D_0042B3B0[] __attribute__((section(".data")));
extern u8 D_0042B3C0[] __attribute__((section(".data")));

s32 func_001018B8(void);
s32 func_002493C0(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_00243A80(s32 a0, s32 a1, s32 a2);
void EftShotFx_Update_2494A0(void);
void func_0026EB78(u8 *a0, u8 *a1);
s32 func_0026EB70(u8 *a0);

/* state (+0xE8 on the object at D_0042A580) +1 and return the new value */
static s32 inc_e8(void) {
    *(s32 *)(D_0042A580 + 0xE8) += 1;
    return *(s32 *)(D_0042A580 + 0xE8);
}

/* FA074 common tail: state++ then the 0x37A6/0x3BBF effect with obj+0xC and obj+0xD8 */
static s32 common_tail(void) {
    u8 *obj = D_0042A580;
    *(s32 *)(obj + 0xE8) += 1;
    return func_002493C0(*(u8 **)(obj + 0xC), 0x37A6, 0x3BBF, 0, *(s32 *)(obj + 0xD8));
}

/* FA160 (states 0x66/0x69) */
static s32 path_160(void) {
    s32 r = func_0026EB70(D_0042A580 + 0x64) & 0x200;
    u8 *g;
    s32 d0;
    if (r == 0) {
        return r;
    }
    g = D_0042A580;
    d0 = *(s32 *)(g + 0xD0);
    *(s32 *)(g + 0xD0) = (d0 & 4) ? (d0 ^ 4) : (d0 | 4);
    return inc_e8();
}

/* FA1A0 (states 0x67/0x6A) */
static s32 path_1A0(void) {
    s32 r = func_0026EB70(D_0042A580 + 0x64) & 0x200;
    if (r != 0) {
        return inc_e8();
    }
    return r;
}

/* 0x003F9F38: effect/timer state machine on the object at D_0042A580 (state byte at +0xE8, 1..0x6B). */
s32 func_003F9F38(void) {
    u8 *obj;
    s32 st;

    obj = D_0042A580;
    st = *(s32 *)(obj + 0xE8);
    if (st == 0) {
        return 0;
    }
    if ((u32)(st - 1) >= 0x6B) {
        return 0;
    }

    switch (st) {
    case 1:
        *(s32 *)(obj + 0xD8) = 0;
        return common_tail();
    case 2:
        if (func_001018B8() == 5) {
            return inc_e8();
        }
        if ((D_003B0C34 & 0x4000) == 0) {
            return D_003B0C34 & 0x4000;
        }
        *(s32 *)(D_0042A580 + 0xE8) = 3;
        return func_00297FE0(0, 1, 0x40, 0x40, 1);
    case 3:
        *(s32 *)(obj + 0xD8) += 1;
        return common_tail();
    case 4:
        if (func_001018B8() == 5) {
            return inc_e8();
        }
        if ((D_003B0C34 & 0x4000) == 0) {
            return 0;
        }
        *(s32 *)(D_0042A580 + 0xE8) = 5;
        return func_00297FE0(0, 1, 0x40, 0x40, 1);
    case 5:
    case 0x6B:
        *(s32 *)(D_0042A580 + 0xE8) = 0;
        return (s32)(long)D_0042A580;
    case 0x33:
        *(s32 *)(obj + 0xD8) = 0x12;
        return common_tail();
    case 0x34:
        if (func_001018B8() == 5) {
            return inc_e8();
        }
        if (D_003B0C34 & 0x4000) {
            *(s32 *)(D_0042A580 + 0xE8) = 0x35;
            return func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        if ((D_003B0C34 & 0x1000) == 0) {
            return 0x35;
        }
        *(s32 *)(D_0042A580 + 0xE8) = 0x35;
        return func_00297FE0(0, 2, 0x40, 0x40, 1);
    case 0x35:
        func_00243A80(0, 0, 0);
        *(s32 *)(D_0042A580 + 0xE8) = 0;
        return (s32)(long)D_0042A580;
    case 0x65:
        EftShotFx_Update_2494A0();
        obj = D_0042A580;
        *(s32 *)(obj + 0xD8) = -1;
        *(s32 *)(obj + 0xDC) = 0;
        func_0026EB78(obj + 0x64, D_0042B3B0);
        *(s32 *)(D_0042A580 + 0xE8) += 1;
        return path_160();
    case 0x66:
    case 0x69:
        return path_160();
    case 0x67:
    case 0x6A:
        return path_1A0();
    case 0x68:
        if ((D_003B0C34 & 0x4000) == 0) {
            return D_003B0C34 & 0x4000;
        }
        if (*(s32 *)(D_0042A580 + 0xDC) < 4) {
            *(s32 *)(D_0042A580 + 0xDC) += 1;
        } else {
            func_0026EB78(D_0042A580 + 0x64, D_0042B3C0);
            *(s32 *)(D_0042A580 + 0xE8) += 1;
        }
        return func_00297FE0(0, 1, 0x40, 0x40, 1);
    default:
        /* jump-table entries that go to the shared exit: v0 = (state - 1) << 2 */
        return (st - 1) * 4;
    }
}
