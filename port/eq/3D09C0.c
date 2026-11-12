#include "common.h"

extern u8 *D_00423120;   /* battle setup state */
extern u8 *D_003876A4;   /* player data */
extern u8 *D_003876A0;   /* game data */

void func_003CFDD0(void);
void func_00243968(s32 a0, s32 a1, s32 a2);
void func_002711A0(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_002438E8(void);
void func_003D1BB0(u8 *b);
void func_003D27A0(u8 *b);
void func_003D3338(u8 *b);
void func_003D80E8(u8 *b);
void func_003D0320(void);
void func_003D0298(void);
void BattleSetup_Finish(void);
void func_002437E8(void);
void func_00271240(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_00101890(void);
void func_00101498(void);
void func_00243A80(s32 a0, s32 a1, s32 a2);
void func_003D0840(s32 *cont);
void func_00101A10(void);
void func_00101AB0(s32 a0, s32 a1, s32 a2, s32 a3);
s64 func_003CFCD0(s32 a0, s32 a1, u8 *a2, s32 *out, s32 n);
s32 func_0024B7F0(s32 a0);
s64 func_0024B110(s32 a0, s32 a1, s32 a2, s32 *out, s32 n);
s64 GetTimerSystemTime(void);
void func_00325370(s64 seed);
s32 rand(void);
s32 func_00101A88(s32 side);
void func_00101AF8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 s0, s32 s1, s32 s2, s32 s3, s32 s4, s32 s5, s64 s6, s32 s7, s32 s8, s32 s9);
s32 func_0024AF50(s32 a0);
void func_00101A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
void func_003D01E0(void);
void func_0028B218(void);

#define B32(off)    (*(s32 *)(D_00423120 + (off)))
#define P32(off)    (*(s32 *)(D_003876A4 + (off)))
#define B_SEL       B32(0x3324)    /* selected team */
#define B_FLAGS     B32(0x2BC)
#define B_SLOTS     ((u16 *)(D_00423120 + 0x353E))   /* [team][8] slot indices */
#define REC(idx)    (D_00423120 + 0x333C + 32 * (idx)) /* 32-byte slot record */
#define REC_FLAGS(r) (*(u16 *)(r))
#define REC_ID(r)    (*(u16 *)((r) + 2))
#define REC_STAT(r)  (*(u16 *)((r) + 0x18))
#define REC_RATE(r)  (*(f32 *)((r) + 0x1C))

s32 func_003D09C0(void) {
    s32 cont;            /* keep-running flag, also set by func_003D0840 */
    s32 stat[2];
    s32 tmp[8];
    s32 e84;
    s32 e88;
    s32 e8c;
    u8 *tbl;
    s32 side;
    s32 slotIdx;
    s32 aiPath;
    u8 *rec;
    s32 base;
    s32 limit;
    s32 value;
    s64 s3v;
    s32 t;
    s32 mode;
    s32 flags;
    s32 i;

    cont = 1;
    func_003CFDD0();
    func_00243968(0, 0, 0);

    for (;;) {
        func_002711A0();
        func_0028B090();
        func_0028BDA0();
        func_00297978();
        func_002438E8();
        mode = P32(0x8C);
        if (mode == 1) {
            func_003D27A0(D_00423120);
        } else if (mode < 2) {
            if (mode == 0) {
                func_003D1BB0(D_00423120);
            }
        } else if (mode == 2) {
            func_003D3338(D_00423120);
        }
        func_003D80E8(D_00423120);
        func_003D0320();
        func_003D0298();
        BattleSetup_Finish();
        func_002437E8();
        func_00271240();
        if (ColorFade_IsInDone()) {
            if (P32(0x18) & 0x10) {
                if (B32(0x330C) == 0) {
                    B32(0x330C) = 1;
                    B32(0x3310) = 0x97;
                }
            } else {
                if (B32(0x330C) == 0) {
                    B32(0x330C) = 1;
                    B32(0x3310) = 0x33;
                }
            }
        }
        if (ColorFade_IsFadingOut()) {
            func_00101890();
            if (cont) {
                func_00101498();
            }
            continue;
        }
        if (ColorFade_IsOutDone()) {
            break;
        }
        flags = B_FLAGS;
        if (flags & 2) {
            B32(0x3308) = B32(0x3308) - 1;
            if (B32(0x3308) == -1) {
                func_00243A80(0, 0, 0);
            }
        } else if (flags & 0x4000) {
            if (flags & 0x80) {
                B_FLAGS = flags | 2;
                B32(0x3308) = 0xF;
                cont = 0;
            }
        } else {
            func_003D0840(&cont);
        }
    }

    if (cont == 0) {
        flags = B_FLAGS;
        if (flags & 0x800) {
            P32(0x88) = P32(0x88) | 2;
        } else if (flags & 0x1000) {
            P32(0x88) = P32(0x88) | 4;
        }
        P32(0x1C) = (B_FLAGS & 0x3800) ? 0x1B : 0x18;
        P32(0x18) = P32(0x18) & ~0x10;
        P32(0x18) = P32(0x18) & ~0x20;
    } else {
        P32(0x18) |= 0x10;
        P32(0x98) = B32(0x3320);
        P32(0x9C) = B32(0x3324);
        __builtin_memcpy(D_003876A4 + 0xA0, D_00423120 + 0x333C, 0x200);
        __builtin_memcpy(D_003876A4 + 0x2A0, D_00423120 + 0x353C, 0xF0);

        e84 = 0;
        e88 = 0;
        e8c = 0x12;
        tbl = *(u8 **)(D_003876A0 + 0x74);
        func_00101A10();
        *(u64 *)(D_003876A0 + 0x4D8) = 0;

        {
            u8 *recA = REC(B_SLOTS[8 * B_SEL]);
            u8 *recB = REC(B_SLOTS[8 * B_SEL + 1]);
            if (REC_FLAGS(recA) & 1) {
                if (REC_FLAGS(recB) & 1) {
                    *(u64 *)(D_003876A0 + 0x4D8) |= 2;
                    stat[0] = 9 * REC_ID(recA) + REC_STAT(recA);
                    stat[1] = 9 * REC_ID(recB) + REC_STAT(recB);
                    func_00101AB0(0, 1, 0, 0);
                    func_00101AB0(1, 1, 0, 0);
                    B_FLAGS |= 0x8000;
                } else {
                    stat[0] = 9 * REC_ID(recA) + REC_STAT(recA);
                    stat[1] = 9 * REC_ID(recB) + REC_STAT(recB);
                    func_00101AB0(0, 1, 0, 0);
                    func_00101AB0(1, 1, 1, 0);
                    B_FLAGS |= 0x10000;
                }
            } else {
                stat[0] = 9 * REC_ID(recB) + REC_STAT(recB);
                stat[1] = 9 * REC_ID(recA) + REC_STAT(recA);
                func_00101AB0(0, 1, 0, 0);
                func_00101AB0(1, 1, 1, 0);
                B_FLAGS |= 0x20000;
            }
        }

        for (side = 0; side < 2; side++) {
            /* which slot belongs to this side, and does it use the AI-timer path */
            if (B_FLAGS & 0x8000) {
                slotIdx = B_SLOTS[8 * B_SEL + side];
                aiPath = 0;
            } else if (B_FLAGS & 0x10000) {
                slotIdx = B_SLOTS[8 * B_SEL + (side ? 1 : 0)];
                aiPath = side != 0;
            } else {
                slotIdx = B_SLOTS[8 * B_SEL + (side ? 0 : 1)];
                aiPath = side != 0;
            }
            rec = REC(slotIdx);

            if (!aiPath) {
                if (REC_FLAGS(rec) & 0x20) {
                    s3v = func_003CFCD0(B32(0x362C), B32(0x3630), rec + 0xA, tmp, 0x14);
                    value = func_0024B7F0(tmp[0]);
                    base = *(s32 *)(tbl + 16 * REC_ID(rec));
                    limit = *(s32 *)(tbl + 16 * REC_ID(rec) + 4);
                    base = base + value;
                } else {
                    s3v = 0;
                    for (i = 7; i >= 0; i--) {
                        tmp[i] = 1;
                    }
                    limit = *(s32 *)(tbl + 16 * REC_ID(rec) + 4);
                    base = *(s32 *)(tbl + 16 * REC_ID(rec));
                }
                value = base;
                if (B32(0x3320) != 0) {
                    mode = P32(0x8C);
                    if (mode < 3 && mode > 0) {
                        f32 fb = (f32)base;
                        s32 part = (s32)(fb * 0x1.999998p-3f);
                        value = (s32)(fb * (REC_RATE(rec) * 0x1.47ae14p-7f)) + part;
                        if (base < value) {
                            value = base;
                        }
                    }
                }
            } else {
                s3v = func_0024B110(B32(0x362C), B32(0x3630),
                                    160 * P32(0x90) + 28 * B32(0x3320) + B32(0x3634) + 0x14,
                                    tmp, 0x7D);
                value = func_0024B7F0(tmp[0]);
                limit = *(s32 *)(tbl + 16 * REC_ID(rec) + 4);
                base = *(s32 *)(tbl + 16 * REC_ID(rec)) + value;
                value = base;
                if (B32(0x3320) != 0) {
                    value = base;
                    if (P32(0x8C) == 1 && !(REC_FLAGS(rec) & 4)) {
                        f32 fb;
                        f32 scale;
                        func_00325370((s32)GetTimerSystemTime());
                        t = rand();
                        fb = (f32)base;
                        scale = (f32)(t % 50) * 0x1.47ae14p-7f;
                        value = (s32)(fb - fb * scale);
                    }
                }
            }

            func_00101AF8(func_00101A88(side) + 8, stat[side], 0,
                          *(s32 *)(*(u8 **)(D_00423120 + 0x3634) + 160 * P32(0x90) + 4 * B32(0x3320)),
                          0, 1, tmp[0], tmp[1],
                          tmp[2], tmp[3], tmp[4], tmp[5], tmp[6], tmp[7],
                          s3v, value, base, limit);
        }

        mode = P32(0x8C);
        if (mode == 1) {
            e88 = 4;
            e84 = func_0024AF50(8);
            e8c = rand() % 7 + 0x15;
            func_00101A60(3, e8c, 0, e88, 0, e84);
        } else if (mode < 2 && mode == 0) {
            e88 = 3;
            e84 = func_0024AF50(7);
            e8c = 0x11;
            func_00101A60(3, e8c, 0, e88, 0, e84);
        } else if (mode == 2) {
            func_00325370((s32)GetTimerSystemTime());
            t = rand() % 6;
            if ((u32)t < 6) {
                switch (t) {
                case 0: e84 = func_0024AF50(0); break;
                case 1: e84 = func_0024AF50(1); break;
                case 2: e84 = func_0024AF50(2); break;
                case 3: e84 = func_0024AF50(3); break;
                case 4: e84 = func_0024AF50(4); break;
                default: e84 = func_0024AF50(6); break;
                }
            }
            e88 = 5;
            e8c = rand() % 12 + 0x11;
            func_00101A60(3, e8c, 0, e88, 0, e84);
        } else {
            func_00101A60(3, e8c, 0, e88, 0, e84);
        }
    }

    func_003D01E0();
    func_0028B218();
    return cont;
}
