#include "common.h"

void List_PushBack(s32 arg0, s32 arg1);
s32 func_0028BAA8(s32 arg0);
void func_0029FC58(s32 arg0);
extern s8 D_00387DB4;
extern s32 D_00387DBC;
extern s32 D_00387DC0;
extern s32 D_00387DC4;
extern s32 D_00387DCC;
extern s32 D_00387DD0;
extern s32 D_003B0F30[] __attribute__((section(".data")));
extern s32 gGscCommands;
extern s32 gGscCurTask;
extern s32 gGscFileFree[] __attribute__((section(".data")));
extern s32 gGscFileList[] __attribute__((section(".data")));
extern s32 gGscTaskList[] __attribute__((section(".data")));

void Gsc_Init(s32 arg0, s32 arg1, s32 arg2) {
    s32 s0;
    s32 s3;
    s32 tmp;

    s3 = 0;
    D_00387DB4 = 1;
    D_00387DC4 = func_0028BAA8(arg1 * 0x24);
    tmp = func_0028BAA8(arg2 * 0x4C);
    gGscCommands = arg0;
    D_00387DD0 = tmp;
    D_00387DC0 = arg1;
    D_00387DBC = 0;
    func_0029FC58((s32)&gGscFileList);
    func_0029FC58((s32)&gGscFileFree);
    D_00387DCC = arg2;
    gGscCurTask = 0;
    func_0029FC58((s32)&gGscTaskList);
    func_0029FC58((s32)&D_003B0F30);

    if (D_00387DC0 > 0) {
        s0 = 0;
        do {
            s3 += 1;
            List_PushBack((s32)&gGscFileFree, D_00387DC4 + s0);
            s0 += 0x24;
        } while (s3 < D_00387DC0);
    }

    s3 = 0;
    if (D_00387DCC > 0) {
        s0 = 0;
        do {
            s3 += 1;
            List_PushBack((s32)&D_003B0F30, D_00387DD0 + s0);
            s0 += 0x4C;
        } while (s3 < D_00387DCC);
    }
}
