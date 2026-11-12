#include "common.h"

extern u8 *D_003877B8;
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);

/* 0x0018E030 EftQuad_Create (BT3 name): 0 if the manager (D_003877B8) or arg0 is null; otherwise
 * BtlTaskList_AddTail(manager->tasks (+0x9688), class 0x00341FB8, arg0). */
s32 EftQuad_Create(s32 arg0) {
    if (D_003877B8 == NULL) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    return BtlTaskList_AddTail(*(s32 *)(D_003877B8 + 0x9688), 0x00341FB8, arg0);
}
