#include "common.h"

s32 List_GetHead(s32 arg0);
s32 List_GetNext(s32 arg0);
extern u8 gGscTaskList[] __attribute__((section(".data")));

s32 Gsc_FindTask(s32 arg0) {
    s32 var_a0;
    s32 var_v0;

    var_a0 = List_GetHead((s32)gGscTaskList);
loop_3:
    var_v0 = 0;
    if (var_a0 != 0) {
        var_v0 = var_a0;
        if (*(s32 *)((u8 *)var_a0 + 0xC) == arg0) {
            return var_v0;
        }
        var_a0 = List_GetNext(var_a0);
        goto loop_3;
    }
    return var_v0;
}
