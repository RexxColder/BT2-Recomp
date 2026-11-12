#include "common.h"

extern s32 func_00217488(u8 *arg0);
extern void BattleSide_SetChara(s32 arg0, s32 arg1);
extern s32 func_00212320(s32 arg0);
extern s32 BtlChar_GetPos(s32 arg0);
extern void BtlAnim_SetNoBlend(s32 arg0);
extern void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 BtlObjXf_Update(s32 arg0);
extern s32 func_001FA3A8(s32 arg0);
extern s32 func_00203C58(s32 a0, s64 a1);
extern s32 func_00203888(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00241718(s32 arg0, s32 arg1);
extern s32 BtlMember_GetActiveGauge(s32 arg0);
extern s32 func_002411E0(s32 arg0, s32 arg1);
extern s32 func_002412A0(void *arg0, s32 arg1, s32 arg2);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00210D98(s32 arg0);
extern s32 func_00241B58(s32 arg0, s32 arg1);

void func_00235568(u8 *chr) {
    s32 charaId;
    s32 type;
    s32 amount;
    s32 flags;
    s32 half;
    s32 timer;
    s32 pad;
    u8 *gauge;

    switch (func_00217488(chr)) {
    case 0xC1: charaId = 0x133; break;
    case 0xC2: charaId = 0x155; break;
    case 0xC3: charaId = 0x177; break;
    case 0xC4: charaId = 0x138; break;
    case 0xC5: charaId = 0x15A; break;
    case 0xC6: charaId = 0x17C; break;
    default: charaId = 0; break;
    }
    BattleSide_SetChara((s32)chr, charaId);
    type = func_00212320((s32)chr);
    *(s32 *)(BtlChar_GetPos((s32)chr) + 0xC0) = 0;
    *(s32 *)(BtlChar_GetPos((s32)chr) + 0xC4) = 0;
    BtlAnim_SetNoBlend((s32)chr);
    func_002113C0(chr, 7, 0x20, 1);
    *(s32 *)(chr + 0xA94) = 0;
    *(s32 *)(chr + 0xA98) = 0;
    *(s32 *)(chr + 0xA9C) = 0;
    *(s32 *)(chr + 0xAA0) = 0;
    *(s32 *)(chr + 0xAA4) = 0;
    func_002113C0(chr, 0xC, 0x1000, 0);
    func_002113C0(chr, 0xC, 0x2000, 0);
    func_002113C0(chr, 0xC, 0x4000, 0);
    if (func_001FA3A8(BtlObjXf_Update((s32)chr)) & 0x10) {
        return;
    }
    if (func_00203C58((s32)chr, 0x10000000) != 0) {
        func_00203888((s32)chr, 100000, 1);
    } else {
        func_00203888((s32)chr, func_00241718((s32)chr, type), 1);
    }
    gauge = (u8 *)BtlMember_GetActiveGauge((s32)chr);
    *(s32 *)(gauge + 0x30 + func_00212320((s32)chr) * 4) += 1;
    if (*(s32 *)(chr + 0xA80) >= 0) {
        func_002113C0(chr, 0xC, 0x1000, 1);
    }
    if (func_002411E0((s32)chr, type) & 0x8000000) {
        return;
    }
    amount = func_002412A0(chr, type, 0);
    if (func_00211310((s32)chr, 0, 0x800) != 0 && type != 4) {
        amount += amount / 5;
    }
    if ((func_002411E0((s32)chr, type) & 0x20000) && func_00211310((s32)chr, 8, 1) == 0) {
        amount = amount * 6 / 10;
    }
    if (amount % 10 != 0) {
        amount = amount - amount % 10 + 10;
    }
    timer = *(s32 *)(chr + 0xA90);
    *(s32 *)(chr + 0x9C4) = amount;
    *(s32 *)(chr + 0x9C8) = amount;
    *(s32 *)(chr + 0x9D0) = timer;
    *(s32 *)(chr + 0x9D4) = 0x8000;
    *(s32 *)(chr + 0x9CC) = amount / (timer + 5);
    switch (type) {
    case 2: *(s32 *)(chr + 0x9D4) = 0x8200; break;
    case 3: *(s32 *)(chr + 0x9D4) = 0x8400; break;
    case 4: *(s32 *)(chr + 0x9D4) = 0x8800; break;
    default: break;
    }
    if (func_00203C58((s32)chr, 0x8000000) != 0) {
        *(s32 *)(chr + 0x9D4) |= 1;
    }
    amount = *(s32 *)(chr + 0x9CC);
    if (amount % 10 != 0) {
        *(s32 *)(chr + 0x9CC) = amount - amount % 10 + 10;
    }
    flags = func_00210D98((s32)chr) & 0x80;
    if (flags == 0) {
        s32 g = func_00241B58((s32)chr, type);
        if (g > 0) {
            s32 lo = *(s32 *)(chr + 0xAA8);
            half = (*(s32 *)(chr + 0xAAC) - lo) / 2;
            if (half <= 0) {
                half = 1;
            }
            *(s32 *)(chr + 0x9D8) = g;
            *(s32 *)(chr + 0x9DC) = g;
            *(s32 *)(chr + 0x9F0) = lo;
            *(s32 *)(chr + 0x9E0) = g / half + 1;
        }
    }
    if (func_002411E0((s32)chr, type) & 0x80) {
        *(s32 *)(chr + 0x9D4) |= 0x10000;
        *(s32 *)(chr + 0x9CC) = 0;
        if (chr[0xA85] != 0) {
            *(s32 *)(chr + 0x9D4) |= 3;
            *(s32 *)(chr + 0x9C8) = 1;
            *(s32 *)(chr + 0x9C4) = 1;
        }
    }
}
