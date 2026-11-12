#include "common.h"

extern u8 *D_003879C0;
extern u8 *D_003876A4;
extern u8 D_003B0B00[];

extern u8 *func_0024C148(void);
extern void func_00251030(s32 arg0);
extern void func_00251088(void);
extern s32 func_0024B4F0(s32 arg0, s32 arg1, s32 arg2);
extern void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00297FE0(s32 a, s32 b, s32 w, s32 h, s32 flag);

/* Menu state M = *D_003879C0, settings S = *D_003876A4. Reads are repeated on purpose: the original re-loads both
 * globals after every call. */
#define M D_003879C0
#define S D_003876A4
#define MW(off) (*(s32 *)(M + (off)))
#define IDX MW(0xC4)
#define CUR MW(0xB0 + 4 * IDX)
#define LIM MW(0xE4 + 4 * IDX)
#define SCR MW(0x2E34 + 4 * IDX)
#define SCR2 MW(0x2E48 + 4 * IDX)
#define PAD_A (*(u32 *)(D_003B0B00 + ((*(s32 *)(S + 0x48C) & 1) ? 0x2C0 : 0x140) + 4))
#define PAD_B (*(u32 *)(D_003B0B00 + ((*(s32 *)(S + 0x48C) & 1) ? 0x2B0 : 0x130) + 4))
#define IS38 (*(s32 *)(S + 0x1C) == 0x38)
/* selected item id of the current list */
#define ITEM (*(s32 *)(M + 4 * (SCR + MW(0xCC)) + 0x90C * IDX + (IS38 ? 0xF4 : 0xF8)))
#define FLAGS16(c) (*(u16 *)((c) + 4 * ITEM + 0x1F30))
#define DONE() func_00297FE0(0, 0, 0x40, 0x40, 1)

s32 func_00252C68(s32 *out)
{
    u32 a;
    u32 b;

    if (MW(0xD8) != 0) {
        if (MW(0xD8) == 1) {
            u8 *m = M;
            if ((*(u32 *)(D_003B0B00 + ((*(s32 *)(S + 0x48C) & 1) ? 0x2B0 : 0x130) + 4) & 0x9000) == 0) {
                return 1;
            }
            func_00251088();
            *(s32 *)(m + 0xD8) = 0;
            return func_00297FE0(0, 2, 0x40, 0x40, 1);
        }
        return 1;
    }
    a = PAD_A;
    if (a & 0x10) {
        s32 v = CUR;
        if (v <= 0) {
            return v;
        }
        CUR = v - 1;
        if (CUR < SCR) {
            SCR = SCR - 1;
            SCR2 = SCR2 - 1;
        }
        return DONE();
    }
    if (a & 0x40) {
        s32 v = CUR;
        if (!(v < LIM - 1)) {
            return v;
        }
        CUR = v + 1;
        if (SCR2 < CUR) {
            SCR = SCR + 1;
            SCR2 = SCR2 + 1;
        }
        return DONE();
    }
    if (a & 0x400) {
        s32 v = CUR;
        if (v <= 0) {
            return v;
        }
        CUR = IS38 ? v - 6 : v - 7;
        while (CUR < 0) {
            CUR = CUR + 1;
        }
        SCR = IS38 ? SCR - 6 : SCR - 7;
        SCR2 = IS38 ? SCR2 - 6 : SCR2 - 7;
        while (SCR < 0) {
            SCR = SCR + 1;
            SCR2 = SCR2 + 1;
        }
        return DONE();
    }
    if (a & 0x800) {
        s32 v = CUR;
        if (!(v < LIM - 1)) {
            return v;
        }
        CUR = IS38 ? v + 6 : v + 7;
        while (LIM - 1 < CUR) {
            CUR = CUR - 1;
        }
        SCR = IS38 ? SCR + 6 : SCR + 7;
        SCR2 = IS38 ? SCR2 + 6 : SCR2 + 7;
        while (LIM - 1 < SCR2) {
            SCR = SCR - 1;
            SCR2 = SCR2 - 1;
        }
        return DONE();
    }
    if (a & 0x100) {
        s32 *w = &CUR;
        if (*w <= 0) {
            return (s32)w;
        }
        *w = 0;
        SCR = 0;
        SCR2 = IS38 ? 5 : 6;
        return DONE();
    }
    if (a & 0x200) {
        s32 v = CUR;
        s32 lim = LIM - 1;
        if (!(v < lim)) {
            return v;
        }
        CUR = lim;
        SCR = IS38 ? LIM - 6 : LIM - 7;
        SCR2 = LIM - 1;
        return DONE();
    }
    if (a & 0x80) {
        IDX = IDX - 1;
        if (IDX < 0) {
            IDX = MW(0xC8) - 1;
        }
        return DONE();
    }
    if (a & 0x20) {
        IDX = IDX + 1;
        if (MW(0xC8) - 1 < IDX) {
            IDX = 0;
        }
        return DONE();
    }
    b = PAD_B;
    if (b & 0x8000) {
        u8 *c = func_0024C148();
        if (FLAGS16(c) & 1) {
            func_00251030(0x3C);
            MW(0xE0) = ITEM;
            MW(0xD8) = 1;
            c = func_0024C148();
            if (FLAGS16(c) & 2) {
                c = func_0024C148();
                FLAGS16(c) = FLAGS16(c) ^ 2;
            }
            return func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        return func_00297FE0(0, 7, 0x40, 0x40, 1);
    }
    if ((b & 0x4000) && IS38) {
        u8 *c = func_0024C148();
        if (FLAGS16(c) & 1) {
            c = func_0024C148();
            if (*(s16 *)(c + 4 * ITEM + 0x1F32) != 0) {
                if (func_0024B4F0(ITEM, *(s32 *)(S + 0x4B0), MW(0x2E5C))) {
                    MW(0xAC) |= 1;
                    MW(0xAC) |= 2;
                    MW(0xD0) = 0xF;
                    c = func_0024C148();
                    if (FLAGS16(c) & 2) {
                        c = func_0024C148();
                        FLAGS16(c) = FLAGS16(c) ^ 2;
                    }
                    return func_00297FE0(0, 1, 0x40, 0x40, 1);
                }
            }
        }
        return func_00297FE0(0, 7, 0x40, 0x40, 1);
    }
    if (PAD_B & 0x1000) {
        func_00243A80(0, 0, 0);
        *out = 0;
        return func_00297FE0(0, 2, 0x40, 0x40, 1);
    }
    return 0;
}
