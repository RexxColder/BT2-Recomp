#include "m2c_macros.h"

s32 BtlTaskList_Update(s32);
void EftHit_BeginFrame(void);
void func_00126F08(void);
void func_00128758(void);
void func_00128EC0(void);
void func_001E4C70(void);
extern s32 *gBtlScene;

// Per-frame battle update: runs the four subsystem steps, then updates the task list of the scene object.
void func_00126258(void) {
    func_00128758();
    func_00128EC0();
    func_001E4C70();
    EftHit_BeginFrame();
    func_00126F08();
    BtlTaskList_Update(*gBtlScene);
}
