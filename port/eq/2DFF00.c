#include "common.h"

s32 func_002DFFD8(s32 arg0, s32 arg1);
void func_002DDBE8(void);
void func_002DE328(void);
void func_002E0050(s32 arg0);
s32 func_002E0058(s32 arg0);
void func_002E00B8(s32 arg0);
void func_002E0190(void);
void func_002E0200(void);
void func_002E0208(s32 arg0, s32 arg1);
void func_002E0790(void);
extern u8 D_0037AFE0[] __attribute__((section(".data")));
extern u8 *D_00399DA0 __attribute__((section(".data")));
extern s32 D_00399DF8 __attribute__((section(".data")));

s32 func_002DFF00(s32 arg0, s32 arg1) {
    s32 v;
    s32 s0;

    D_00399DA0 = D_0037AFE0;
    v = func_002DFFD8(arg0, arg1);
    if (v == 0) {
        func_002E0050(0);
        func_002E0208(arg0, func_002E0058(arg1));
        s0 = D_00399DF8;
        func_002DDBE8();
        func_002DE328();
        func_002E00B8(s0 + 0x17E0);
        func_002E0190();
        func_002E0200();
        func_002E0790();
        return 0;
    }
    if (v == (s32)0xFF03FF05) {
        return v;
    }
    while (1) {
    }
}
