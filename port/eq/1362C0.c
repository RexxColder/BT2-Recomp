#include "common.h"

/* 0x001362C0: if (!(gBtlStage->flags(+8) & 1) && EftStage_IsDrawOn() && !func_00276D00()) func_00136A00(). */
extern u8 *gBtlStage;
s32 EftStage_IsDrawOn(void);
s32 func_00276D00(void);
void func_00136A00(void);

void func_001362C0(void) {
    if ((*(u32 *)(gBtlStage + 8) & 1) != 0) {
        return;
    }
    if (EftStage_IsDrawOn() == 0) {
        return;
    }
    if (func_00276D00() != 0) {
        return;
    }
    func_00136A00();
}
