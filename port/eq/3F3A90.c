#include "common.h"

extern u8 *D_0042A570;
extern u8 *D_003876A4;
extern u8 *D_00387F2C;
void func_003F0BF8();
void func_00243968();
void func_002711A0();
void func_003F0800();
void func_0028B090();
void func_0028C0A8();
void func_00297978();
void func_002438E8();
void func_003F2498();
void func_003F2438();
void func_003F16E0();
void BattleSetup_Finish();
void func_002437E8();
void func_00271240();
s32 ColorFade_IsInDone();
s32 ColorFade_IsFadingOut();
s32 ColorFade_IsOutDone();
s32 func_0026EB60();
void func_002493C0();
void func_003F3810();
void func_00101890();
void func_00101498();
void func_00243A80();
void func_003F25C0();
void func_003F1630();
void func_0028B218();

#define O D_0042A570
#define P D_003876A4
#define OW(off) (*(s32 *)(O + (off)))
#define PW(off) (*(s32 *)(P + (off)))

s32 func_003F3A90(s32 arg0) {
    s32 sp[4];

    sp[0] = 1;
    func_003F0BF8(arg0);
    func_00243968(0, 0, 0);
    for (;;) {
        func_002711A0();
        func_003F0800();
        func_0028B090();
        func_0028C0A8();
        func_00297978();
        func_002438E8();
        func_003F2498();
        func_003F2438();
        func_003F16E0();
        BattleSetup_Finish();
        func_002437E8();
        func_00271240();
        if (ColorFade_IsInDone()) {
            if (OW(0x36C8) == 0) {
                if (func_0026EB60(O + 0x4C) == 0) {
                    OW(0x36C8) = 1;
                    func_002493C0(0, 0x37A6, 0x3BBF, 0, 0xC);
                }
            }
        }
        if (OW(0x218) & 0xC000) {
            if (OW(0x36B8) == 4) {
                func_003F3810();
            }
            continue;
        }
        if (ColorFade_IsFadingOut()) {
            func_00101890();
            func_00101498();
            continue;
        }
        if (ColorFade_IsOutDone()) {
            if (OW(0x36B8) == 4) {
                break;
            }
            continue;
        }
        if ((OW(0x218) & 0xC00) == 0xC00) {
            s32 v = OW(0x36C4) - 1;
            OW(0x36C4) = v;
            if (v == -1) {
                func_00243A80(0, 0, 0);
                PW(0x390) = OW(0x21C) + OW(0x224) * 7;
                PW(0x3A4) = OW(0x220) + OW(0x228) * 7;
                PW(0x408) = OW(0x22C);
                PW(0x41C) = OW(0x230);
                PW(0x430) = OW(0x23C);
                PW(0x444) = OW(0x240);
            }
        } else if (OW(0x36CC) == 0) {
            func_003F25C0(sp);
        }
    }
    if (sp[0]) {
        s32 t0;
        PW(0x40) = PW(0x40) & ~1;
        PW(0x40) = PW(0x40) & ~2;
        t0 = *(s32 *)(*(u8 **)(O + 0x36D0) + PW(0x64) * 56 + 0xC);
        if (t0 == 2) {
            PW(0x44) = *(s32 *)(*(u8 **)(O + 0x258) + (OW(0x21C) + OW(0x224) * 7) * 44);
            PW(0x48) = *(s32 *)(*(u8 **)(O + 0x25C) + (OW(0x220) + OW(0x228) * 7) * 44);
            PW(0x4C) = OW(0x21C) + OW(0x224) * 7;
            PW(0x50) = OW(0x220) + OW(0x228) * 7;
            PW(0x70) = OW(0x23C);
            PW(0x74) = OW(0x240);
        } else {
            t0 = 1;
            PW(0x44) = *(s32 *)(*(u8 **)(O + 0x258) + (OW(0x21C) + OW(0x224) * 7) * 44);
            PW(0x48) = -1;
            PW(0x4C) = OW(0x21C) + OW(0x224) * 7;
            PW(0x50) = -1;
            PW(0x70) = OW(0x23C);
            PW(0x74) = OW(0x240);
        }
        PW(0x68) = t0;
        if (OW(0x218) & 0x40000) {
            PW(0x40) = PW(0x40) | 1;
        }
        if (OW(0x218) & 0x80000) {
            PW(0x40) = PW(0x40) | 2;
        }
        PW(0x6C) = *(s32 *)(*(u8 **)(O + 0x36D0) + PW(0x64) * 56 + 4) - 1;
        *(s32 *)(D_00387F2C + 0x208) |= 2 << PW(0x64);
    }
    func_003F1630();
    func_0028B218();
    return sp[0];
}
