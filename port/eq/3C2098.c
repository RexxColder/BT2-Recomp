#include "common.h"

extern u8 *D_00421C98;
extern u8 *D_00387F2C;
extern u8 *D_003876A4;
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern u8 D_003B0B00[];
extern u8 D_004229B8[];
extern u8 D_004229C8[];
extern s32 func_0029C7C0();
extern s32 func_0029C7E0();
extern s32 func_0029C7F0();
extern s32 func_0029C640();
extern s32 func_0029C550();
extern s32 func_0029C820();
extern s32 func_0029C830();
extern s32 func_0029C800();
extern s32 func_0029C1E8();
extern s32 func_00297FE0();
extern s32 func_00288348();
extern s32 func_00289C98();
extern s32 func_0028A578();
extern void func_002984E0(s32 arg0);
extern s32 func_002493C0();
extern s32 func_0026EB78();
extern s32 func_0024C0F0();
extern s32 func_003C1A48();
extern s32 McCard_GetInfo();
extern s32 McCard_IsFatalError();

#define PAD(o) (*(s32 *)(D_003B0B00 + (o)))

s32 func_003C2098(void) {
    u8 *b;
    u8 *cur;
    s32 st;
    s32 v;
    s32 t;
    s32 s0;

    st = *(s32 *)(D_00421C98 + 0x9A4) - 1;
    if ((u32)st >= 0xD) {
        return 0;
    }
    if ((u32)st >= 0xC) {
        cur = D_00421C98;
        goto end28;
    }
    switch (st) {
    case 0:
        func_0029C7C0(1);
        func_0029C7F0(*(s32 *)(D_00421C98 + 0x14));
        b = D_00421C98;
        *(s32 *)(b + 0x130) = 1;
        b = D_00421C98;
        v = *(s32 *)(b + 0x9A8);
        if (v <= 0) {
            if (v >= 0) {
                goto l24f0;
            }
            *(s32 *)(b + 0x9A4) = 0xA;
            goto l216c;
        }
        t = *(s32 *)(b + 0x9AC) - 1;
        *(s32 *)(b + 0x9AC) = t;
        if (t >= 0) {
            goto end24;
        }
        b = D_00421C98;
        *(s32 *)(b + 0x124) |= 8;
        b = D_00421C98;
        *(s32 *)(b + 0x9A4) = 0xA;
        b = D_00421C98;
        *(s32 *)(b + 0x9AC) = 0x78;
    l216c:
        b = D_00421C98;
        *(s32 *)(b + 0x9A8) = 0;
        goto end24;
    case 1:
        func_0029C7C0(0);
        func_0029C640(0);
        func_0029C7E0(0);
        func_0029C7F0(*(s32 *)(D_00421C98 + 0x14));
        b = D_00421C98;
        *(s32 *)(b + 0x130) = 2;
        b = D_00421C98;
        v = *(s32 *)(b + 0x9AC);
        if (v > 0) {
            *(s32 *)(b + 0x9AC) = v - 1;
            goto end24;
        }
        if (!(PAD(0x134) & 0x4000)) {
            goto end24;
        }
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        b = D_00421C98;
        func_00288348(b);
        *(s32 *)(b + 0x9AC) = 0x78;
        b = D_00421C98;
        *(s32 *)(b + 0x9A4) = 3;
        goto end24;
    case 2:
        func_0029C7E0(1);
        func_0029C7C0(0);
        b = D_00421C98;
        t = *(s32 *)(b + 0x9AC) - 1;
        *(s32 *)(b + 0x9AC) = t;
        if (t < 0) {
            b = D_00421C98;
            func_0029C7F0(*(s32 *)(b + 0x10));
            b = D_00421C98;
            *(s32 *)(b + 0x130) = 0x2E;
            b = D_00421C98;
            if (func_00289C98(0, b + 0x584) != 0) {
                b = D_00421C98;
                *(s32 *)(b + 0x124) |= 4;
                *(s32 *)(D_00387F2C + 0xE08) |= 1;
                b = D_00421C98;
                *(s32 *)(b + 0x9A4) = 0xA;
                func_002984E0(0x186A0);
                b = D_00421C98;
                *(s32 *)(b + 0x9A4) = 0xA;
                t = 0x78;
                goto l23c8;
            }
            if (*(s32 *)(gMcCardPort + 0xC) != 2) {
                goto l23a8;
            }
            if (McCard_IsFatalError(*(s32 *)(gMcCardPort + 8)) != 0) {
                goto l23a8;
            }
            if (*(s32 *)(gMcCardPort + 8) >= 0) {
                goto end28_reload;
            }
            b = D_00421C98;
            *(s32 *)(b + 0x9A4) = 4;
            goto end24;
        }
        b = D_00421C98;
        func_0029C7F0(*(s32 *)(b + 0x10));
        b = D_00421C98;
        *(s32 *)(b + 0x130) = 0x2E;
        if (McCard_GetInfo(0) == 0) {
            goto end28_reload;
        }
        b = D_00421C98;
        if (*(s32 *)(b + 0x9AC) > 0) {
            goto end28_reload;
        }
        if (*(s32 *)(gMcCardPort + 0xC) != 2) {
            s0 = 5;
            *(s32 *)(b + 0x9A4) = 5;
            goto l23b0;
        }
        if (McCard_IsFatalError(*(s32 *)(gMcCardPort + 8)) == 0) {
            goto end28_reload;
        }
    l23a8:
        b = D_00421C98;
        s0 = 5;
        *(s32 *)(b + 0x9A4) = 5;
    l23b0:
        b = D_00421C98;
        func_0029C7F0(*(s32 *)(b + 0x10));
        b = D_00421C98;
        *(s32 *)(b + 0x130) = s0;
        t = 0xB4;
    l23c8:
        b = D_00421C98;
        *(s32 *)(b + 0x9AC) = t;
        goto end24;
    case 3:
        func_0029C7C0(0);
        b = D_00421C98;
        func_0029C7F0(*(s32 *)(b + 0x10));
        b = D_00421C98;
        *(s32 *)(b + 0x130) = 0x2E;
        if (func_0028A578(0, 0) == 0) {
            if (McCard_IsFatalError(*(s32 *)(gMcCardPort + 8)) == 0) {
                goto end28_reload;
            }
            goto l23a8;
        }
        b = D_00421C98;
        if (*(s32 *)(gMcCardPort + 8) == 1) {
            *(s32 *)(b + 0x9A4) = 5;
            b = D_00421C98;
            func_0029C7F0(*(s32 *)(b + 0x10));
            b = D_00421C98;
            v = 0x2D;
        } else {
            *(s32 *)(b + 0x9A4) = 5;
            b = D_00421C98;
            func_0029C7F0(*(s32 *)(b + 0x10));
            b = D_00421C98;
            v = 0x2C;
        }
        *(s32 *)(b + 0x130) = v;
        b = D_00421C98;
        *(s32 *)(b + 0x9AC) = 0x78;
        goto end24;
    case 4:
        func_0029C7C0(0);
        if (!(PAD(0x134) & 0x4008)) {
            goto end24;
        }
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        func_0029C820(1);
        b = D_00421C98;
        *(s32 *)(b + 0x9A4) = 0xC;
        goto end24;
    case 9:
        func_0029C7C0(0);
        func_0029C550(1);
        b = D_00421C98;
        *(s32 *)(b + 0x9A4) = 0xB;
        goto end24;
    case 10:
        func_0029C7C0(0);
        func_0029C640(0);
        if (func_0029C830() == 0) {
            goto end24;
        }
        b = D_00421C98;
        *(s32 *)(b + 0x9A4) = 0;
        if (*(s32 *)(D_00387F2C + 0xE08) & 1) {
            b = D_00421C98;
            *(s32 *)(b + 0x128) = 0;
            b = D_00421C98;
            *(s32 *)(D_003876A4 + 0x4B8) = *(s32 *)(b + 0x128);
            b = D_00421C98;
            func_0026EB78(b + 0x68, D_004229B8);
            func_00297FE0(2, 5, 0x40, 0x40, 1);
        }
        b = D_00421C98;
        v = *(s32 *)(b + 0x124);
        if (v & 4) {
            v = 0x10;
        } else if (v & 8) {
            v = 0xD;
        } else {
            b = D_00421C98;
            func_003C1A48(b);
            func_0026EB78(b + 0x68, D_004229C8);
            cur = (u8 *)func_0024C0F0();
            goto end28;
        }
        *(s32 *)(b + 0x12C) = v;
        b = D_00421C98;
        func_002493C0(*(s32 *)(b + 8), 0x33E9, 0x3802, 0, *(s32 *)(b + 0x12C));
        goto end28_reload;
    case 11:
        func_0029C7C0(1);
        b = D_00421C98;
        *(s32 *)(b + 0x130) = 0x30;
        b = D_00421C98;
        v = *(s32 *)(b + 0x9A8);
        if (v <= 0) {
            if (v < -1) {
                *(s32 *)(b + 0x9A4) = 2;
                b = D_00421C98;
                *(s32 *)(b + 0x9A8) = 0;
                func_00288348(b);
                goto end28_reload;
            }
        l24f0:
            v = func_0029C640(0);
            b = D_00421C98;
            *(s32 *)(b + 0x9A8) = v;
            b = D_00421C98;
            *(s32 *)(b + 0x9AC) = 0xC;
            goto end24;
        }
        t = *(s32 *)(b + 0x9AC) - 1;
        *(s32 *)(b + 0x9AC) = t;
        if (t >= 0) {
            goto end24;
        }
        b = D_00421C98;
        *(s32 *)(b + 0x9A4) = 0xA;
        b = D_00421C98;
        *(s32 *)(b + 0x9A8) = 0;
        goto end24;
    default:
        break;
    }
end24:
end28_reload:
    cur = D_00421C98;
end28:
    func_0029C800(*(s32 *)(cur + 0x130));
    return func_0029C1E8(1);
}
