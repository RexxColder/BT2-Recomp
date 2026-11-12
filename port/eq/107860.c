#include "common.h"

extern u8 *gObjOutline;
extern u8 D_003B0C34[];

extern void func_001075F0(u8 *m);
extern void func_00107548(u8 *m, s32 idx, s32 flag);
extern s32 func_0028C648(u8 *m);
extern s32 BtlMenu_IsSkillList(u8 *m);
extern s32 BtlMenu_IsControls(u8 *m);
extern s32 func_00106958(u8 *m);
extern s32 func_00106B58(u8 *m);
extern s32 func_00106C98(u8 *m);
extern void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* One step of the menu cursor machine for menu `m` (items: 0x20-byte records at m[0], count m[4],
   cursor m[0x18], state m[0x1C]: 0/1 slide in toward `other`, 2/3 slide back, 4 = input handling).
   Returns 1 when the slide-back finishes. `parent` is the caller flag, `pad` the pad index. */
s32 func_00107860(u8 *parent, u8 *other, u8 *m, s32 pad) {
    u8 *items;
    u8 *cur;
    u8 *ent;
    u32 keys;
    s32 audio;
    s32 state;
    s32 i;
    s32 step;
    s32 prev;
    s32 n;
    s32 idx;
    s32 ax, ay, bx, by;
    f32 f1, f2;
    s32 r;

    gObjOutline[4] = 1;
    *(s32 *)(gObjOutline + 8) = pad;
    func_001075F0(m);

    idx = *(s32 *)(m + 0x14);
    if (idx >= 0) {
        items = *(u8 **)m;
        if (*(s32 *)(items + idx * 32 + 8) != 0) {
            func_00107548(m, idx, 0);
            r = func_00107860(parent, m, *(u8 **)(*(u8 **)m + *(s32 *)(m + 0x14) * 32 + 8), pad);
            if (r != 1) {
                return 0;
            }
            *(*(u8 **)m + *(s32 *)(m + 0x14) * 32 + 0x1A) = 0;
            *(s32 *)(m + 0x14) = -1;
            return 0;
        }
        *(s32 *)(m + 0x14) = -1;
    } else {
        items = *(u8 **)m;
    }

    idx = *(s32 *)(m + 0x18);
    ent = items + idx * 32;
    if (*(s32 *)(ent + 0xC) != 0 && ent[0x1A] != 0) {
        goto final_check;
    }

    keys = *(u32 *)(D_003B0C34 + pad * 0x180);
    if (func_0028C648(m)) {
        keys = 0;
    }
    audio = 0;
    if (!BtlMenu_IsSkillList(m)) {
        if (!BtlMenu_IsControls(m)) {
            audio = 1;
            if (func_00106958(m)) {
                audio = 0;
            }
        }
    }

    state = *(s32 *)(m + 0x1C);
    if ((u32)state >= 5) {
        goto final_check;
    }
    switch (state) {
    case 0:
        func_00297FE0(0, 4, 0x40, 0x40, 1);
        *(s32 *)(m + 0x1C) = 1;
        ax = func_00106B58(other);
        ay = func_00106C98(other);
        bx = func_00106B58(m);
        by = func_00106C98(m);
        f1 = (f32)(bx - ax);
        f2 = (f32)(by - ay);
        *(s32 *)(m + 0x30) = 0;
        *(f32 *)(m + 0x20) = (f32)ax;
        *(f32 *)(m + 0x24) = (f32)ay;
        *(f32 *)(m + 0x28) = f1 / 6.0f;
        *(f32 *)(m + 0x2C) = f2 / 6.0f;
        /* fallthrough */
    case 1:
        f1 = *(f32 *)(m + 0x20) + *(f32 *)(m + 0x28);
        f2 = *(f32 *)(m + 0x24) + *(f32 *)(m + 0x2C);
        n = *(s32 *)(m + 0x30) + 1;
        *(s32 *)(m + 0x30) = n;
        *(f32 *)(m + 0x20) = f1;
        *(f32 *)(m + 0x24) = f2;
        if (n < 6) {
            goto final_check;
        }
        *(f32 *)(m + 0x20) = (f32)func_00106B58(m);
        r = func_00106C98(m);
        *(s32 *)(m + 0x1C) = 4;
        *(f32 *)(m + 0x24) = (f32)r;
        goto final_check;
    case 2:
        func_00297FE0(0, 5, 0x40, 0x40, 1);
        *(s32 *)(m + 0x1C) = 3;
        ax = func_00106B58(other);
        ay = func_00106C98(other);
        bx = func_00106B58(m);
        by = func_00106C98(m);
        f1 = (f32)(ax - bx);
        f2 = (f32)(ay - by);
        *(s32 *)(m + 0x30) = 0;
        *(f32 *)(m + 0x20) = (f32)bx;
        *(f32 *)(m + 0x24) = (f32)by;
        *(f32 *)(m + 0x28) = f1 / 6.0f;
        *(f32 *)(m + 0x2C) = f2 / 6.0f;
        /* fallthrough */
    case 3:
        f1 = *(f32 *)(m + 0x20) + *(f32 *)(m + 0x28);
        f2 = *(f32 *)(m + 0x24) + *(f32 *)(m + 0x2C);
        n = *(s32 *)(m + 0x30) + 1;
        *(s32 *)(m + 0x30) = n;
        *(f32 *)(m + 0x20) = f1;
        *(f32 *)(m + 0x24) = f2;
        if (n < 6) {
            goto final_check;
        }
        *(f32 *)(m + 0x20) = (f32)func_00106B58(other);
        r = func_00106C98(other);
        *(s32 *)(m + 0x1C) = 0;
        *(f32 *)(m + 0x24) = (f32)r;
        return 1;
    case 4:
        if (pad >= 0) {
            if (*(u8 **)(gObjOutline + 0xC) == m) {
                if ((keys & 0x1008) != 0 && parent == 0) {
                    *(s32 *)(m + 0x1C) = 2;
                    goto final_check;
                }
            } else if (keys & 0x1000) {
                *(s32 *)(m + 0x1C) = 2;
                goto final_check;
            }
        }
        step = 0;
        prev = *(s32 *)(m + 0x18);
        if (pad >= 0) {
            if (keys & 0x10) {
                if (audio) {
                    func_00297FE0(0, 0, 0x40, 0x40, 1);
                }
                step = -1;
            }
            if (keys & 0x40) {
                if (audio) {
                    func_00297FE0(0, 0, 0x40, 0x40, 1);
                }
                step = 1;
            }
        }
        *(s32 *)(m + 0x18) = *(s32 *)(m + 0x18) + step;
        items = *(u8 **)m;
        n = *(s32 *)(m + 4);
        for (;;) {
            idx = *(s32 *)(m + 0x18);
            if (idx < 0) {
                *(s32 *)(m + 0x18) = n - 1;
                idx = n - 1;
            }
            if (!(idx < n)) {
                *(s32 *)(m + 0x18) = 0;
                idx = 0;
            }
            if (idx == prev) {
                break;
            }
            if (items[idx * 32 + 0x19] == 0) {
                break;
            }
            *(s32 *)(m + 0x18) = idx + step;
        }
        ent = items + idx * 32;
        if (pad < 0 || !(keys & 0x4000)) {
            goto final_check;
        }
        ent[0x1D] = 1;
        if (*(s32 *)(ent + 8) != 0) {
            *(s32 *)(m + 0x14) = *(s32 *)(m + 0x18);
            func_00107860(parent, m, *(u8 **)(*(u8 **)m + *(s32 *)(m + 0x18) * 32 + 8), pad);
            if (*(s32 *)(ent + 0xC) == 0) {
                goto final_check;
            }
            ent[0x1C] = 1;
            ent[0x1A] = 1;
            goto final_check;
        }
        if (*(s32 *)(ent + 0xC) != 0) {
            ent[0x1C] = 1;
            ent[0x1A] = 1;
            goto final_check;
        }
        r = *(s32 *)(ent + 0x14);
        if (r != 0) {
            if (r == 2) {
                *(s32 *)(m + 0x1C) = r;
            }
            goto final_check;
        }
        r = *(s32 *)(m + 0x10);
        if (r == 1) {
            for (i = 0; i < *(s32 *)(m + 4); i++) {
                (*(u8 **)m)[i * 32 + 0x18] = 0;
            }
            ent[0x18] = 1;
        } else if (r == 2) {
            ent[0x18] = ent[0x18] ^ 1;
            if (ent[0x18] == 0) {
                goto final_check;
            }
            n = *(s32 *)(m + 4);
            if (n <= 0) {
                goto final_check;
            }
            idx = *(s32 *)(m + 0x18);
            for (i = 0; i < n; i++) {
                if (i != idx) {
                    (*(u8 **)m)[i * 32 + 0x18] = 0;
                    idx = *(s32 *)(m + 0x18);
                    n = *(s32 *)(m + 4);
                }
            }
            goto final_check;
        } else if (r == 0) {
            ent[0x18] = ent[0x18] ^ 1;
        }
        goto final_check;
    }

final_check:
    idx = *(s32 *)(m + 0x18);
    ent = *(u8 **)m + idx * 32;
    if (*(s32 *)(ent + 8) == 0) {
        func_00107548(m, idx, 1);
    }
    return 0;
}
