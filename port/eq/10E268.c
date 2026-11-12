#include "common.h"

s32 func_00203CC0(s32 a0);
s32 func_0010B0A0(s32 arg0);
void func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0020B108(u32 arg0);
u8 *func_00208700(s32 arg0);
s32 func_0020BFE8(u32 arg0);
s32 func_0010DEA8(u8 *obj, u8 *ctx, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 mask);
void func_00113860(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(u8 *arg0, s32 arg1);
void func_00113B00(u8 *arg0, s32 arg1, s32 arg2);
void func_001140A8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
s32 Ramp_Step(s32 arg0);
f32 Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
extern f32 D_00383E34;
extern f32 D_00383E38;
extern f32 D_00383E3C;
extern f32 D_00383E40;

void func_0010E268(u8 *base, s32 idx, s32 who) {
    u8 *r = (u8 *)(u32)func_00203CC0(who);
    s32 g = func_0010B0A0(idx);
    u8 *ctx = base + idx * 0x750 + 0xD0;
    s32 hud = g + 0x1AA0;
    s32 unit = *(s32 *)(r + 0x10) / 5;
    s32 state = *(s32 *)(ctx + 0x6C4);
    s32 secDiv, rem1, q1, q2, a0r, a1r, vis, full, i, acc, off;
    u8 *obj, *p;
    s32 *slot;
    s32 xpos;

    if (state != 2 && *(s32 *)(r + 0xC) < *(s32 *)(ctx + 0x6CC)) {
        *(s32 *)(ctx + 0x6D0) = 0;
    }
    if (state == 1) {
        s32 cnt = *(s32 *)(ctx + 0x6D0);
        *(s32 *)(ctx + 0x6D0) = cnt + 1;
        if (cnt >= 7) {
            *(s32 *)(ctx + 0x6C4) = 2;
        }
        *(s32 *)(ctx + 0x6CC) = *(s32 *)(r + 0xC);
    } else if (state < 2) {
        if (state == 0) {
            s32 old;
            *(s32 *)(ctx + 0x6D0) = 0;
            old = *(s32 *)(ctx + 0x6CC);
            if (*(s32 *)(r + 0xC) < old) {
                *(s32 *)(ctx + 0x6C4) = 1;
            }
            if (old == *(s32 *)(r + 0xC)) {
                *(s32 *)(ctx + 0x6C8) = *(s32 *)(r + 0xC);
            } else {
                *(s32 *)(ctx + 0x6C8) = old;
            }
        }
        *(s32 *)(ctx + 0x6CC) = *(s32 *)(r + 0xC);
    } else if (state == 2) {
        s32 v = *(s32 *)(ctx + 0x6C8) - 2500;
        *(s32 *)(ctx + 0x6C8) = v;
        if (*(s32 *)(r + 0xC) < v) {
            *(s32 *)(ctx + 0x6CC) = *(s32 *)(r + 0xC);
        } else {
            *(s32 *)(ctx + 0x6C4) = 0;
            *(s32 *)(ctx + 0x6CC) = *(s32 *)(r + 0xC);
        }
    } else {
        *(s32 *)(ctx + 0x6CC) = *(s32 *)(r + 0xC);
    }

    secDiv = *(s32 *)(r + 0x1C) / 6000;
    q1 = *(s32 *)(ctx + 0x6C8) / unit;
    q2 = *(s32 *)(r + 0xC) / unit;
    rem1 = *(s32 *)(r + 0x1C) - secDiv * 6000;
    a0r = *(s32 *)(r + 0xC) - q2 * unit;
    a1r = *(s32 *)(ctx + 0x6C8) - q1 * unit;
    if (a0r == 0 && q2 != 0) {
        a0r = unit;
        q2 = q2 - 1;
    }
    if (func_0020B108(who)) {
        vis = (s32)(u32)func_00208700(who) / unit;
    } else {
        vis = 0;
    }
    func_00114508(hud, 2, 0, 0x3D);
    xpos = 0x40;
    if (func_0020BFE8(who)) {
        for (i = 0; i < 5; i++) {
            *(s32 *)(ctx + 0x6E8 + i * 4) = 0;
        }
        full = 0;
    } else {
        full = 1;
        i = 0;
        if (*(s32 *)(ctx + 0x6E8) == 2) {
            for (i = 1; i < 5; i++) {
                if (*(s32 *)(ctx + 0x6E8 + i * 4) != 2) {
                    full = 0;
                    break;
                }
            }
        } else {
            full = 0;
        }
    }
    if (full) {
        if (Ramp_Step((s32)(u32)(ctx + 0x2C))) {
            if (*(f32 *)(ctx + 0x3C) != 1.0f) {
                Ramp_Start((s32)(u32)(ctx + 0x2C), D_00383E34, 0.5f, 1.0f);
            } else {
                Ramp_Start((s32)(u32)(ctx + 0x2C), D_00383E38, 1.0f, 0.5f);
            }
        }
    } else {
        Ramp_Start((s32)(u32)(ctx + 0x2C), D_00383E3C, D_00383E40, 1.0f);
        *(s32 *)(ctx + 0x3C) = 0;
    }

    p = ctx + 0x6E8;
    obj = (u8 *)(u32)hud;
    slot = (s32 *)(ctx + 0x6D4);
    off = 0;
    acc = 0;
    for (i = 0; i < 5; i++) {
        s32 mask = (i < vis) << 18;
        u8 *hs = (u8 *)(u32)hud + i * 0x60;
        u8 *sp = hs + 0x14A0;

        if (*(s32 *)(r + 0x1C) != 0) {
            if (secDiv == i) {
                func_0010DEA8(obj, ctx, unit, 0, rem1, xpos, 0x1B, unit, 0x1770, mask);
            } else if (i < secDiv) {
                func_0010DEA8(obj, ctx, unit, 0, 0x1770, xpos, 0x1B, unit, 0x1770, mask);
            } else {
                func_0010DEA8(obj, ctx, unit, 0, 0, xpos, 0x1B, unit, 0x1770, mask);
            }
        } else if (q2 == i) {
            if (q1 == i) {
                func_0010DEA8(obj, ctx, a0r, a1r, 0, xpos, 0x1B, unit, 0x1770, mask);
            } else if (i < q1) {
                func_0010DEA8(obj, ctx, a0r, unit, 0, xpos, 0x1B, unit, 0x1770, mask);
            } else {
                func_0010DEA8(obj, ctx, a0r, 0, 0, xpos, 0x1B, unit, 0x1770, mask);
            }
        } else if (i < q2) {
            func_0010DEA8(obj, ctx, unit, 0, 0, xpos, 0x1B, unit, 0x1770, mask);
        } else if (q1 == i) {
            func_0010DEA8(obj, ctx, 0, a1r, 0, xpos, 0x1B, unit, 0x1770, mask);
        } else if (i < q1) {
            func_0010DEA8(obj, ctx, 0, unit, 0, xpos, 0x1B, unit, 0x1770, mask);
        } else {
            func_0010DEA8(obj, ctx, 0, 0, 0, xpos, 0x1B, unit, 0x1770, mask);
        }

        if (*(s32 *)(r + 0xC) - acc < unit) {
            *(s32 *)(ctx + 0x3C) = 0;
            func_00113860(sp + 0xC, 0, 0, 0x40, 0x14, 0x12);
            func_00113D80(sp, 0);
            func_00113B00(sp, xpos - 14, 0x15);
            {
                s32 v = *slot - 6;
                if (v < 0) {
                    v = 0;
                }
                *slot = v;
                if (v != 0) {
                    sp[0x19] = (u8)*slot;
                } else {
                    *(s32 *)sp = 0;
                }
            }
            *(s32 *)p = 0;
        } else {
            if (*(s32 *)(r + 0x1C) != 0) {
                if (i < secDiv) {
                    func_00113860(hs + 0x14AC, 0, 0x16, 0x40, 0x2A, 0x12);
                } else {
                    func_00113860(hs + 0x14AC, 0, 0, 0x40, 0x14, 0x12);
                }
                func_00113D80(sp, 0);
                func_00113B00(sp, xpos - 14, 0x15);
            } else {
                func_00113860(hs + 0x14AC, 0, 0, 0x40, 0x14, 0x12);
                func_00113D80(sp, 0);
                func_00113B00(sp, xpos - 14, 0x15);
            }
            if (*(s32 *)p == 0) {
                *(s32 *)(ctx + 4 + off + 0x6D0) = 100;
                *(s32 *)p = 1;
            } else if (*(s32 *)p == 1) {
                s32 *q = (s32 *)(ctx + 4 + off + 0x6D0);
                s32 v = *q - 6;
                *q = v;
                if (v < 0) {
                    *q = 0;
                    *(s32 *)p = 2;
                }
            } else {
                *slot = 0;
            }
            if (full != 0) {
                f32 f = *(f32 *)(ctx + 0x3C);
                if (0.0f < f) {
                    *slot = (u32)(f * 45.0f) & 0xFF;
                }
            }
            if (*slot != 0) {
                sp[0x19] = (u8)*slot;
            } else {
                *(s32 *)sp = 0;
            }
        }
        off += 4;
        p += 4;
        xpos += 0x19;
        slot++;
        acc += unit;
        obj += 0x420;
    }
    if (idx == 1) {
        func_001140A8((u8 *)(u32)hud, 0, 1, 0, 0x3D);
    }
    BtlRec_CallFlagged(hud, 1, 0x3D);
}
