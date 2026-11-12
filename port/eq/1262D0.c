#include "common.h"
#include "battle/btl_scene.h"

void func_00126DA8(void);
void BtlScene_ClearStageChangeRequest(void);
void BtlScene_CreateLayers(void *group);
void func_00126C00(void);
void BtlTaskList_Reset(void *root, s32 tag);

/* 0x001262D0: scene reset. Calls func_00126DA8 and BtlScene_ClearStageChangeRequest, then a switch on the
 * argument (0..4) resets the root task list with tag 0, 0x800, 0x1000 or 0x2000 (case 1 also calls
 * func_00126C00 and then creates the layers from gBtlScene->group). Other values do nothing. */
void BtlScene_Reset(s32 arg0) {
    func_00126DA8();
    BtlScene_ClearStageChangeRequest();
    switch (arg0) {
        case 0:
            BtlTaskList_Reset(gBtlScene->root, 0);
            break;
        case 1:
            BtlTaskList_Reset(gBtlScene->root, 0);
            func_00126C00();
            BtlScene_CreateLayers(gBtlScene->group);
            return;
        case 2:
            BtlTaskList_Reset(gBtlScene->root, 0x800);
            break;
        case 3:
            BtlTaskList_Reset(gBtlScene->root, 0x1000);
            break;
        case 4:
            BtlTaskList_Reset(gBtlScene->root, 0x2000);
            break;
        default:
            return;
    }
}
