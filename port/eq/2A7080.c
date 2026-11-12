#include "common.h"

s32 Gsc_GetInt(void);
void Gsc_ResetOperands(void);
void func_002A6F98(s32 arg0, s32 arg1);
void func_002AD380(s32 arg0);
extern s32 D_003B26B0[] __attribute__((section(".data")));

void func_002A7080(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        D_003B26B0[1] = 1;
        D_003B26B0[2] = Gsc_GetInt();
        D_003B26B0[3] = Gsc_GetInt();
        func_002AD380(D_003B26B0[2]);
    }
    Gsc_ResetOperands();
    func_002A6F98(arg0, arg1);
}
