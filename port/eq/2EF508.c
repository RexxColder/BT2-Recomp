#include "common.h"

void func_002EE4D0(void);
void func_002EE578(s32 arg0, s32 arg1);
void func_002EE630(void);
void func_002EE6B8(void);
void func_002EE740(void);
void func_002EE7D8(s32 arg0, s32 arg1);
void func_002EDC10(void);
void func_002EDC98(void);
void func_002EDDF0(void);
void func_002EDE18(void);
void func_00307700(s32 arg0, s32 arg1, s32 arg2);
void func_003077D8(s32 arg0, s32 arg1);
void func_003077F0(s32 arg0, s32 arg1);
void func_00307AF8(u8 *arg0, s32 arg1);
void func_0032EAF0(s32 arg0, s32 arg1);
s32 func_0032EB50(s32 arg0, s32 arg1);
void func_0032EB60(s32 arg0, u8 *arg1);
extern s32 D_0034BB60 __attribute__((section(".data")));
extern s32 D_0034BB68 __attribute__((section(".data")));
extern u8 D_0034BB70[] __attribute__((section(".data")));
extern s32 D_0034BC08 __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern s32 gFileReq __attribute__((section(".data")));

void func_002EF508(u8 *arg0) {
    s32 sp[12];
    u8 *dst;
    s32 a0v;
    s32 a1v;

    if (gFileReq == 0) {
        func_00307AF8(arg0, D_0034BB60);
        func_003077D8((s32)func_002EDC10, 0);
        func_003077F0((s32)func_002EDC98, 0);
        dst = D_0034BB70;
        if (arg0 != NULL) {
            *(s32 *)(dst + 0x14) = *(s32 *)(arg0 + 0x14);
            *(s32 *)(dst + 0x20) = *(s32 *)(arg0 + 0x20);
            a1v = *(s32 *)(arg0 + 0x28);
            *(s32 *)(dst + 0x0) = *(s32 *)(arg0 + 0x0);
            *(s32 *)(dst + 0x28) = a1v;
            *(u32 *)(dst + 0x4) = *(u32 *)(arg0 + 0x4);
            *(s32 *)(dst + 0x8) = *(s32 *)(arg0 + 0x8);
            *(s32 *)(dst + 0xC) = *(s32 *)(arg0 + 0xC);
            *(s32 *)(dst + 0x10) = *(s32 *)(arg0 + 0x10);
            *(s32 *)(dst + 0x18) = *(s32 *)(arg0 + 0x18);
            *(s32 *)(dst + 0x1C) = *(s32 *)(arg0 + 0x1C);
            *(s32 *)(dst + 0x24) = *(s32 *)(arg0 + 0x24);
            *(s32 *)(dst + 0x2C) = *(s32 *)(arg0 + 0x2C);
            a0v = (s32)dst;
        } else {
            a0v = 8;
            a1v = 0xF;
            *(s32 *)(dst + 0x14) = 0x18;
            *(s32 *)(dst + 0x0) = 1;
            *(u32 *)(dst + 0x4) = 8;
            *(s32 *)(dst + 0x8) = 0xF;
            *(s32 *)(dst + 0xC) = 0x10;
            *(s32 *)(dst + 0x10) = 0x12;
            *(s32 *)(dst + 0x18) = 0x19;
            *(s32 *)(dst + 0x1C) = 0x1A;
            *(s32 *)(dst + 0x2C) = 0;
            *(s32 *)(dst + 0x20) = 0;
            *(s32 *)(dst + 0x24) = 0;
            *(s32 *)(dst + 0x28) = 0;
        }
        D_0034BC08 = func_0032EB50(a0v, a1v);
        func_0032EB60(D_0034BC08, (u8 *)sp);
        D_00353498 = sp[6];
        func_002EE4D0();
        func_002EE578(*(s32 *)(D_0034BB70 + 0x20), *(s32 *)(D_0034BB70 + 0x24));
        func_002EE630();
        func_002EE6B8();
        func_002EE740();
        func_002EE7D8(*(s32 *)(D_0034BB70 + 0x28), *(s32 *)(D_0034BB70 + 0x2C));
        func_0032EAF0(D_0034BC08, *(s32 *)(D_0034BB70 + 0x14));
        func_00307700(6, (s32)func_002EDDF0, 0);
        func_00307700(7, (s32)func_002EDE18, 0);
        D_0034BB68 = 1;
    }
    gFileReq += 1;
}
