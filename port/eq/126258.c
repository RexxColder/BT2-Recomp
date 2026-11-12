#include "common.h"

/* 0x00126258: func_00128758(a0); func_00128EC0(); func_001E4C70(); EftHit_BeginFrame(); func_00126F08();
   then tail BtlTaskList_Update(gBtlScene->+0). */
extern u8 *gBtlScene;
void func_00128758(void);
void func_00128EC0(void);
void func_001E4C70(void);
void EftHit_BeginFrame(void);
void func_00126F08(void);
void BtlTaskList_Update(s32 arg0);

void func_00126258(s32 a0) {
    func_00128758();
    func_00128EC0();
    func_001E4C70();
    EftHit_BeginFrame();
    func_00126F08();
    BtlTaskList_Update(*(s32 *)gBtlScene);
}
