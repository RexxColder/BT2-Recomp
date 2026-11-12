#include "common.h"

/* 0x001262A0: func_00127BB8(); func_00127388(<a0..a5 as left by the asm>); BtlTaskList_PostUpdate(gBtlScene->+0);
   then tail call func_00126CC8 (its a0 is whatever the callee left). */
extern u8 *gBtlScene;

void func_00127BB8(void);
void func_00127388();
void BtlTaskList_PostUpdate(s32 arg0);
s32 func_00126CC8(void);

s32 func_001262A0(void) {
    func_00127BB8();
    func_00127388();
    BtlTaskList_PostUpdate(*(s32 *)gBtlScene);
    return func_00126CC8();
}
