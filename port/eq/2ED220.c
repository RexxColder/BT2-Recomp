#include "common.h"

extern s32 D_0034AEC0 __attribute__((section(".data")));
extern s32 D_0034AEC8 __attribute__((section(".data")));
extern s32 D_0034AED0 __attribute__((section(".data")));
extern s32 D_0034AED4 __attribute__((section(".data")));
extern s32 D_0034AED8 __attribute__((section(".data")));
extern u8 D_0034AEE0[] __attribute__((section(".data")));
extern u8 D_0037C228[] __attribute__((section(".data")));
extern u8 D_0037C278[] __attribute__((section(".data")));
extern u8 D_0037C288[] __attribute__((section(".data")));
extern u8 D_0037C298[] __attribute__((section(".data")));
extern u8 *D_0039D6C0 __attribute__((section(".data")));
extern u8 func_002ED168[] __attribute__((section(".data")));
extern u8 func_002ED180[] __attribute__((section(".data")));
extern u8 func_002ED1C0[] __attribute__((section(".data")));
extern u8 func_002ED1E0[] __attribute__((section(".data")));
extern u8 func_002ED200[] __attribute__((section(".data")));

void func_002E9360(s32 arg0);
void func_002E93C0(void);
void func_002E93D8(void);
void func_00305410(void);
void func_00304660(void);
void BtlGame_Term(void);
void func_002E9FB8(void);
void func_002F17E0(void);
void func_002F00D8(void);
void func_0030A450(void);
void func_002EFD50(void);
void func_00300898(void);
void func_00307AF8(void);
void func_002EFD80(void *arg0, s32 arg1);
void func_003007D0(void *arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00307590(s32 arg0, s32 arg1, void *arg2, s32 arg3, void *arg4);
s32 func_00307378(s32 arg0, void *arg1, s32 arg2, void *arg3);
void func_002F55D8(s32 arg0, s32 arg1, s32 arg2);

void func_002ED220(void) {
    s32 temp = D_0034AEC0;

    D_0039D6C0 = D_0037C228;
    if (temp == 0) {
        func_002E9360(temp);
        func_002E93C0();
        func_00305410();
        func_00304660();
        BtlGame_Term();
        func_002E9FB8();
        func_002F17E0();
        func_002F00D8();
        func_0030A450();
        func_002EFD50();
        func_00300898();
        func_00307AF8();
        func_002EFD80(func_002ED168, 0);
        func_003007D0(func_002ED180, 0);
        memset(D_0034AEE0, 0, 0xC80);
        func_00307590(2, 1, func_002ED1E0, 0, D_0037C278);
        D_0034AED4 = func_00307378(4, func_002ED200, 0, D_0037C288);
        D_0034AEC8 = func_00307378(5, func_002ED1C0, 0, D_0037C298);
        D_0034AED8 = 0;
        D_0034AED0 = 0;
        /* lui-only arguments: the %hi value of D_0034AEC8 / D_0034AED0 (0x350000), not their addresses */
        func_002F55D8(0x3C, 0x350000, 0x350000);
        func_002E93D8();
        temp = D_0034AEC0;
    }
    D_0034AEC0 = temp + 1;
}
