#include "common.h"

void Gsc_StepTask(s32 arg0);
s32 List_GetHead(void *list);
s32 List_GetNext(s32 node);
extern u8 D_00387DB4;
extern s32 gGscCurTask;
extern u8 gGscTaskList[] __attribute__((section(".data")));

void func_0029F250(void) {
    s32 node;
    s32 cur;

    if (D_00387DB4 != 0) {
        node = List_GetHead(gGscTaskList);
        if (node != 0) {
            do {
                cur = node;
                node = List_GetNext(node);
                Gsc_StepTask(cur);
            } while (node != 0);
        }
        gGscCurTask = 0;
    }
}
