#include "common.h"

extern u8 *D_00421C98 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003C0950(s32 arg0);
void func_003C0F58(void);
void func_003C0FD0(void);
void func_003C1AA0(void);
void func_003C1B90(s32 *out);
void func_003C2098(void);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
s32 func_26EB60(u8 *p);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003C2668: sibling of 0x3E09A0 on D = D_00421C98 (0x12C and 0x13C gate arms 0x13C = 1, 0x124 bits 2 / 1 and
 * 0x134 == 1, countdown 0x138; on -1: P->0x4B8 = G->0x128 and P->0x4B4 gets bit 0 when 0x124 & 1 and 0x134 == 1,
 * else loses it; P = D_3876A4). */
s32 func_003C2668(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003C0950(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003C1AA0();
        func_003C0FD0();
        func_003C2098();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_00421C98 + 0x12C) == 0 &&
            *(s32 *)(D_00421C98 + 0x13C) == 0 && func_26EB60(D_00421C98 + 0x68) != 0) {
            *(s32 *)(D_00421C98 + 0x13C) = 1;
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (*(s32 *)(D_00421C98 + 0x124) & 2) {
                v = *(s32 *)(D_00421C98 + 0x138) - 1;
                *(s32 *)(D_00421C98 + 0x138) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x4B8) = *(s32 *)(D_00421C98 + 0x128);
                    if ((*(s32 *)(D_00421C98 + 0x124) & 1) && *(s32 *)(D_00421C98 + 0x134) == 1) {
                        *(s32 *)(D_3876A4 + 0x4B4) = *(s32 *)(D_3876A4 + 0x4B4) | 1;
                    } else {
                        *(s32 *)(D_3876A4 + 0x4B4) = *(s32 *)(D_3876A4 + 0x4B4) & ~1;
                    }
                }
            } else {
                func_003C1B90(sp);
            }
            continue;
        }
        break;
    }
    func_003C0F58();
    func_28B218();
    return sp[0];
}
