#include "common.h"

extern u8 *D_00423114 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern s32 D_003876AC __attribute__((section(".data")));

s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2);
s32 func_00243A80(s32 a0, s32 a1, s32 a2);
void func_00243968(s32 a0, s32 a1, s32 a2);
void func_0028BB60(s32 arg0);
void func_0029BD28(u8 *arg0);
s32 func_00250978(s32 arg0);
void func_002539C8(s32 arg0);
s32 func_0029BB88(u8 *a0, s32 a1);

/* 0x003CA360: enter/leave a sub-state on the object at D_00423114 (flags word +0x18C,
   entry table at +0x190 indexed by +0x188), with a 0x37/0x38 step loop on D_003876A4 (+0x1C). */
s32 func_003CA360(void) {
    u8 *obj;
    u8 *g;
    u8 *entry;
    u8 *m;
    s32 flags;
    s32 result;
    s32 saved;
    s32 cont;
    s32 state;
    s32 a1;

    obj = D_00423114;
    flags = *(s32 *)(obj + 0x18C);

    if (!(flags & 0x10000)) {
        *(s32 *)(obj + 0x18C) = flags | 0x10000;
        func_00100D58(*(s32 *)(D_003876A4 + 4) + 14, 0, 1);
        return func_00243A80(0, 0, 0);
    }

    result = flags & 0x20000;
    if (result != 0) {
        return result;
    }

    result = func_00100D58(0, 0, 0);
    D_003876AC = result;
    if (result == 0) {
        return result;
    }

    obj = D_00423114;
    *(s32 *)(obj + 0x18C) = *(s32 *)(obj + 0x18C) | 0x20000;
    flags = *(s32 *)(obj + 0x18C);

    if (flags & 0x4000) {
        if (*(s32 *)(obj + 0x188) != 0) {
            *(s32 *)(D_003876A4 + 0x48C) |= 2;
        }
    } else if (flags & 0x8000) {
        if (*(s32 *)(obj + 0x188) != 0) {
            *(s32 *)(D_003876A4 + 0x48C) |= 2;
        }
        *(s32 *)(D_003876A4 + 0x48C) |= 1;
    }

    obj = D_00423114;
    entry = obj + *(s32 *)(obj + 0x188) * 4 + 0x190;
    a1 = *(s32 *)(entry + 8);
    *(s32 *)(D_003876A4 + 0x494) = *(s32 *)entry + a1 * 7;

    saved = *(s32 *)(D_003876A4 + 0x1C);
    *(s32 *)(D_003876A4 + 0x1C) = 0x37;
    func_0029BD28(entry);

    cont = 1;
    while (cont) {
        g = D_003876A4;
        state = *(s32 *)(g + 0x1C);
        if (state == 0x37) {
            if (func_00250978(1) != 0) {
                *(s32 *)(D_003876A4 + 0x1C) = 0x38;
            } else {
                cont = 0;
            }
        } else if (state == 0x38) {
            func_002539C8(2);
            *(s32 *)(D_003876A4 + 0x1C) = 0x37;
        }
    }

    *(s32 *)(D_003876A4 + 0x1C) = saved;

    obj = D_00423114;
    flags = *(s32 *)(obj + 0x18C);
    if (flags & 0x4000) {
        *(s32 *)(obj + 0x18C) = flags ^ 0x4000;
    } else if (flags & 0x8000) {
        *(s32 *)(obj + 0x18C) = flags ^ 0x8000;
    }

    obj = D_00423114;
    *(s32 *)(obj + 0x18C) &= 0xFFFEFFFF;
    *(s32 *)(obj + 0x18C) &= 0xFFFDFFFF;
    *(s32 *)(D_003876A4 + 0x48C) &= -2;
    *(s32 *)(D_003876A4 + 0x48C) &= -3;

    func_00243968(0, 0, 0);
    func_0028BB60(D_003876AC);
    D_003876AC = 0;

    obj = D_00423114;
    m = *(u8 **)(obj + 4);
    a1 = *(s32 *)(obj + 0x1C);
    return func_0029BB88(m + ((*(u32 *)(m + 0x58) >> 2) << 2), a1);
}
