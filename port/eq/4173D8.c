#include "common.h"

extern u8 *D_0042BB7C;
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern u8 *D_003876A4;
extern s32 func_0029C7C0();
extern s32 func_0029C640();
extern s32 func_0029C800();
extern s32 func_0029C1E8();
extern s32 func_0029C550();
extern s32 func_0029C830();
extern s32 func_00288348();
extern s32 func_00289C98();
extern s32 func_0028A578();
extern s32 func_004121A8();
extern s32 McCard_GetInfo();
extern s32 McCard_IsFatalError();
extern s32 McCard_ReadFile();
extern s32 McCard_Checksum();

s32 func_004173D8(void) {
    u8 *b;
    s32 st;
    s32 v;
    s32 t;
    s32 mode;

    b = D_0042BB7C;
    st = *(s32 *)(b + 0x3768);
    if (st == 0) {
        return 0;
    }
    if ((u32)(st - 1) >= 11) {
        goto end70;
    }
    switch (st) {
    case 1:
        func_0029C7C0(0);
        b = D_0042BB7C;
        *(s32 *)(b + 0x3764) = 0x22;
        func_0029C640(0);
        b = D_0042BB7C;
        t = *(s32 *)(b + 0x376C) - 1;
        *(s32 *)(b + 0x376C) = t;
        if (t < 0) {
            b = D_0042BB7C;
            if (func_00289C98(1, b + 0x3774) != 0) {
                *(s32 *)(b + 0x376C) = 0x78;
                *(s32 *)(D_0042BB7C + 0x3768) = 3;
                goto end6c;
            }
            st = *(s32 *)(gMcCardPort + 0x30);
            if (st != 2) {
                goto e7;
            }
            if (McCard_IsFatalError(*(s32 *)(gMcCardPort + 0x2C)) == 0) {
                if (*(s32 *)(gMcCardPort + 0x2C) >= 0) {
                    goto end70;
                }
                *(s32 *)(D_0042BB7C + 0x3768) = st;
                goto end6c;
            }
            goto e7;
        }
        if (McCard_GetInfo(1) == 0) {
            goto end70;
        }
        b = D_0042BB7C;
        if (*(s32 *)(b + 0x376C) > 0) {
            goto end70;
        }
        if (*(s32 *)(gMcCardPort + 0x30) != 2) {
            *(s32 *)(b + 0x3768) = 7;
            *(s32 *)(D_0042BB7C + 0x376C) = 0x78;
            goto end6c;
        }
        if (McCard_IsFatalError(*(s32 *)(gMcCardPort + 0x2C)) == 0) {
            goto end70;
        }
    e7:
        b = D_0042BB7C;
        *(s32 *)(b + 0x3768) = 7;
        *(s32 *)(D_0042BB7C + 0x376C) = 0x78;
        goto end6c;
    case 2:
        func_0029C7C0(0);
        b = D_0042BB7C;
        *(s32 *)(b + 0x3764) = 0x22;
        if (func_0028A578(1, 1) != 0) {
            if (*(s32 *)(gMcCardPort + 0x2C) == 1) {
                v = 6;
            } else {
                v = 8;
            }
        } else {
            if (McCard_IsFatalError(*(s32 *)(gMcCardPort + 0x2C)) == 0) {
                goto end6c;
            }
            v = 7;
        }
        b = D_0042BB7C;
        goto set940;
    case 3:
        func_0029C7C0(0);
        b = D_0042BB7C;
        *(s32 *)(b + 0x3764) = 8;
        b = D_0042BB7C;
        t = *(s32 *)(b + 0x376C) - 1;
        *(s32 *)(b + 0x376C) = t;
        if (t >= 0) {
            if (McCard_GetInfo(1) == 0) {
                goto end6c;
            }
            if (McCard_IsFatalError(*(s32 *)(gMcCardPort + 0x2C)) == 0) {
                goto end6c;
            }
            v = 5;
            b = D_0042BB7C;
            goto set940;
        }
        b = D_0042BB7C;
        if (McCard_ReadFile(1, b + 0x7B94, 0x4000, b + 0x3774) == 0) {
            if (*(s32 *)(gMcCardPort + 0x2C) >= 0) {
                goto end70;
            }
            b = D_0042BB7C;
            v = 5;
            goto set940;
        }
        b = D_0042BB7C;
        if (*(s32 *)(gMcCardPort + 0x24) & 1) {
            v = 6;
            goto set940;
        }
        if (McCard_Checksum(b + 0x7B94, 0x4000, 0) == 0) {
            u8 *p = D_003876A4;
            *(s32 *)(*(u8 **)p + 0x4C8) = (s32)(D_0042BB7C + 0x3B94);
            p = D_003876A4;
            *(s32 *)(*(u8 **)p + 0x4CC) = (s32)(D_0042BB7C + 0x7B94);
            p = D_003876A4;
            *(u32 *)(*(u8 **)p + 0x18) |= 0x2000;
            *(s32 *)(D_0042BB7C + 0x3768) = 4;
            *(s32 *)(D_0042BB7C + 0x376C) = 0x78;
            goto end6c;
        }
        v = 6;
        b = D_0042BB7C;
        goto set940;
    case 4:
        func_0029C7C0(0);
        b = D_0042BB7C;
        *(s32 *)(b + 0x3764) = 0xA;
        b = D_0042BB7C;
        t = *(s32 *)(b + 0x376C) - 1;
        *(s32 *)(b + 0x376C) = t;
        if (t >= 0) {
            goto end6c;
        }
        func_004121A8(b);
        *(s32 *)(D_0042BB7C + 0x3768) = 9;
        goto end6c;
    case 5:
        mode = 9;
        goto timer4c;
    case 6:
        mode = 0x19;
        goto timer4c;
    case 7:
        mode = 5;
        goto timer4c;
    case 8:
        mode = 7;
    timer4c:
        func_0029C7C0(0);
        b = D_0042BB7C;
        *(s32 *)(b + 0x3764) = mode;
        b = D_0042BB7C;
        t = *(s32 *)(b + 0x376C) - 1;
        *(s32 *)(b + 0x376C) = t;
        if (t >= 0) {
            goto end6c;
        }
        *(s32 *)(D_0042BB7C + 0x3768) = 0xB;
        goto end6c;
    case 9:
        func_0029C7C0(0);
        func_0029C550(1);
        *(s32 *)(D_0042BB7C + 0x3768) = 0xA;
        goto end6c;
    case 10:
        func_0029C7C0(0);
        func_0029C640(0);
        if (func_0029C830() == 0) {
            goto end6c;
        }
        *(s32 *)(D_0042BB7C + 0x3768) = 0;
        func_00288348();
        goto end70;
    case 11:
        func_0029C7C0(1);
        b = D_0042BB7C;
        *(s32 *)(b + 0x3764) = 0x30;
        b = D_0042BB7C;
        t = *(s32 *)(b + 0x3770);
        if (t > 0) {
            *(s32 *)(b + 0x3768) = 9;
            *(s32 *)(D_0042BB7C + 0x3770) = 0;
            goto end6c;
        }
        if (t >= 0) {
            v = func_0029C640(0);
            b = D_0042BB7C;
            *(s32 *)(b + 0x3770) = v;
            *(s32 *)(D_0042BB7C + 0x376C) = 0xC;
            goto end6c;
        }
        t = *(s32 *)(b + 0x376C) - 1;
        *(s32 *)(b + 0x376C) = t;
        if (t >= 0) {
            goto end6c;
        }
        b = D_0042BB7C;
        *(s32 *)(b + 0x3768) = 1;
        *(s32 *)(D_0042BB7C + 0x376C) = 0x78;
        *(s32 *)(D_0042BB7C + 0x3770) = 0;
        func_00288348();
        goto end70;
    }
set940:
    *(s32 *)(b + 0x3768) = v;
    *(s32 *)(D_0042BB7C + 0x376C) = 0x78;
end6c:
end70:
    func_0029C800(*(s32 *)(D_0042BB7C + 0x3764));
    return func_0029C1E8(1);
}
