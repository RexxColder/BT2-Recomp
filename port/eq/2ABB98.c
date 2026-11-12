#include "common.h"

extern u8 D_003B2654[];
extern u8 D_003B2600[];
extern s32 D_003876A0;
extern u8 D_003450C0[];
extern u8 D_003450D8[];
extern u8 D_003450F0[];
extern u8 D_00345108[];
extern u8 D_00345120[];

void func_001012D0(void);
s32 func_002ABB40(void);
s32 func_00100CB8(s32 arg0);
s32 func_0029F518(s32 arg0);
s32 func_002ACF90(s32 arg0, s32 arg1);
void func_002AC9C0(void);
void func_002A85B0(void);
void func_002AB7B0(u8 *arg0);
void func_002AB7F0(s32 arg0, s32 arg1);
void func_002998D8(void);
void func_002A3328(void);
s32 Gsc_StartAction(s32 arg0, s32 arg1);
void func_0029F250(void);
s32 func_0029F6F8(s32 arg0);
void func_002A3510(void);
void func_002ABE80(void);
s32 func_002AC1F8(void);
s32 Gsc_StartMain(s32 arg0);
s32 BtlStage_IsReady(void);
void func_001F42F8(s32 arg0);
s32 func_002AB860(void);
void func_00126578(s32 arg0);
void func_00126098(s32 arg0);

/* 0x002ABB98 (per-frame stage/scene state step). Works on the global record D_003B2654: the step counter at +0x5C
 * (switch 0..4 via jtbl_00377A80 sets the table pointer at +0x58 and a bit of the 64-bit flags word at D_003876A0+0x4D8),
 * then the common scene calls. Returns 1 when the step counter is 2 after the calls, 0 otherwise. */
s32 func_002ABB98(void) {
    u8 *s0 = D_003B2654;
    u8 *s2 = s0 + 0x5C;
    u8 *g;
    s32 s1;
    s32 v0;
    s32 state;
    s32 a3;
    s32 a0v;

    func_001012D0();
    s0[0x18] = 0;
    v0 = func_002ABB40();
    s0[0x54] = 0;
    if (v0 != 0) {
        s1 = *(s32 *)(s2 + 0x28);
    } else {
        s1 = *(s32 *)(s0 + 4);
    }

    v0 = func_00100CB8(s1);
    *(s32 *)(s0 + 0x14) = v0;
    v0 = func_0029F518(v0);
    *(s32 *)(s0 + 0xC) = v0;
    v0 = func_002ACF90(s1, *(s32 *)(s0 + 0x44));
    if (*(s32 *)(s0 + 0x44) != -1) {
        *(s32 *)(s0 + 0x48) = *(s32 *)(s0 + 0x44);
    }
    *(s32 *)(s0 + 0x44) = -1;
    func_002AC9C0();

    g = (u8 *)D_003876A0;
    *(u64 *)(g + 0x4D8) &= ~((u64)7 << 35);

    state = *(s32 *)s2;
    if (state < 5) {
        switch (state) {
        case 0:
            *(s32 *)(s0 + 0x58) = (s32)D_003450C0;
            break;

        case 1:
            *(u64 *)(g + 0x4D8) |= (u64)1 << 37;
            *(s32 *)(s0 + 0x58) = (s32)D_003450D8;
            *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 4);
            break;

        case 2:
            *(u64 *)(g + 0x4D8) |= (u64)1 << 36;
            *(s32 *)(s0 + 0x58) = (s32)D_003450F0;
            break;

        case 3:
            *(u64 *)(g + 0x4D8) |= (u64)1 << 36;
            *(s32 *)(s0 + 0x58) = (s32)D_00345108;
            break;

        case 4:
            *(u64 *)(g + 0x4D8) |= (u64)1 << 35;
            *(s32 *)(s0 + 0x58) = (s32)D_00345120;
            break;

        default:
            break;
        }
    }

    func_002A85B0();
    func_002AB7B0(s0);
    func_002AB7F0((s32)s0, *(s32 *)s2);
    func_002998D8();
    func_002A3328();
    *(s32 *)(s0 + 0x10) = Gsc_StartAction(*(s32 *)(s0 + 0xC), 0x3E9);
    while (func_0029F6F8(*(s32 *)(s0 + 0x10)) != 0) {
        func_0029F250();
    }

    *(s32 *)(D_003B2600 + 0x54) = *(s32 *)(D_003B2600 + 0x54) & ~0x300;

    a3 = *(s32 *)(s2 + 4);
    if (a3 == 3) {
        a0v = *(s32 *)(s2 + 0x20);
        *(s32 *)(D_003B2600 + 0x54) = *(s32 *)(D_003B2600 + 0x54) | (s32)0x80000000;
        if ((a0v & 1) != 0) {
            *(s32 *)(s2 + 0x20) = a0v & ~1;
        }
    }

    if (a3 == 2) {
        *(s32 *)(s0 + 0x58) = (s32)D_003450C0;
        func_0029F250();
        func_002A3510();
        func_002ABE80();
        func_002AC1F8();
        return 1;
    }

    *(s32 *)(s0 + 0x10) = Gsc_StartMain(*(s32 *)(s0 + 0xC));
    if (BtlStage_IsReady() == 0) {
        return 0;
    }
    func_001F42F8(s1);
    v0 = func_002AB860();
    func_00126578(v0);
    func_00126098(2);
    return 0;
}
