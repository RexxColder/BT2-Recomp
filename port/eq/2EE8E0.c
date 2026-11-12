#include "common.h"

void func_002EE4D0(void);
void func_002EE630(void);
void func_002EE6B8(void);
void func_002EE740(void);
void func_00307700(s32 arg0, void *arg1, s32 arg2);
void func_003077D8(void *arg0, s32 arg1);
void func_003077F0(void *arg0, s32 arg1);
void func_00307AF8(void *arg0, s32 arg1, s32 arg2);
void func_0032EAF0(s32 arg0, s32 arg1);
s32 func_0032EB50(s32 *arg0);
void func_0032EB60(s32 arg0, s32 *arg1);
void func_002EDC10(void);
void func_002EDC98(void);
void func_002EDDF0(void);

extern s32 D_0034BB60 __attribute__((section(".data")));
extern s32 D_0034BB70[] __attribute__((section(".data")));
extern s32 D_0034BBBC __attribute__((section(".data")));
extern s32 D_0034BC08 __attribute__((section(".data")));
extern s32 D_00353498 __attribute__((section(".data")));
extern s32 D_0039D6C8[] __attribute__((section(".data")));
extern s32 D_0039D6D0[] __attribute__((section(".data")));
extern s32 gFileReq __attribute__((section(".data")));

void func_002EE8E0(s32 *arg0) {
    s32 sp[12];

    D_0034BBBC = 0;
    if (gFileReq == 0) {
        func_00307AF8(arg0, gFileReq, D_0034BB60);
        func_003077D8(func_002EDC10, 0);
        func_003077F0(func_002EDC98, 0);
        D_0039D6C8[1] = 0;
        D_0039D6C8[0] = 0;
        D_0039D6D0[1] = 0;
        D_0039D6D0[0] = 0;
        if (arg0 == NULL) {
            D_0034BB70[6] = 0x19;
            D_0034BB70[5] = 0x18;
            D_0034BB70[0] = 1;
            D_0034BB70[1] = 8;
            D_0034BB70[3] = 0x10;
            D_0034BB70[4] = 0x12;
        } else {
            D_0034BB70[5] = arg0[4];
            D_0034BB70[0] = arg0[0];
            D_0034BB70[1] = arg0[1];
            D_0034BB70[3] = arg0[2];
            D_0034BB70[4] = arg0[3];
            D_0034BB70[6] = arg0[5];
        }
        D_0034BC08 = func_0032EB50(D_0034BB70);
        func_0032EB60(D_0034BC08, sp);
        D_00353498 = sp[6];
        func_002EE4D0();
        func_002EE630();
        func_002EE6B8();
        func_002EE740();
        func_0032EAF0(D_0034BC08, D_0034BB70[5]);
        func_00307700(6, func_002EDDF0, 0);
    }
    gFileReq += 1;
}
