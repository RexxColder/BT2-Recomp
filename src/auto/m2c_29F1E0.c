#include "m2c_macros.h"

M2C_UNK func_0028BB60(s32);                         /* extern */
M2C_UNK func_0029FC58(M2C_UNK *);                   /* extern */
extern s8 D_00387DB4;
extern s32 D_00387DC4;
extern s32 D_00387DD0;
extern M2C_UNK D_003B0F30 __attribute__((section(".data")));
extern s32 gGscCommands;
extern s32 gGscCurTask;
extern M2C_UNK gGscFileFree __attribute__((section(".data")));
extern M2C_UNK gGscFileList __attribute__((section(".data")));
extern M2C_UNK gGscTaskList __attribute__((section(".data")));

void func_0029F1E0(void) {
    func_0029FC58(&gGscFileList);
    func_0029FC58(&gGscFileFree);
    func_0029FC58(&gGscTaskList);
    func_0029FC58(&D_003B0F30);
    func_0028BB60(D_00387DC4);
    func_0028BB60(D_00387DD0);
    D_00387DB4 = 0;
    gGscCommands = 0;
    gGscCurTask = 0;
}
