#include "m2c_macros.h"

s32 BtlTaskList_PostUpdate(s32);
void func_00126CC8(void);
void func_00127388(void);
void func_00127BB8(void);
extern s32 *gBtlScene;

// Post-update step of the battle frame: runs two subsystem steps, then BtlTaskList_PostUpdate on the scene object, then tail-calls func_00126CC8.
void func_001262A0(void) {
    func_00127BB8();
    func_00127388();
    BtlTaskList_PostUpdate(*gBtlScene);
    func_00126CC8();
}
