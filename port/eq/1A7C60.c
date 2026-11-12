#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);
void EftStruggle_Update(s32 arg0);
extern u8 *gEftStruggle;

s32 EftStruggle_GetPos(s32 arg0) {
    u8 *mgr;
    u8 *list;
    u8 *task;
    u8 *cls;

    mgr = gEftStruggle;
    if (mgr == NULL) {
        return 0;
    }
    list = *(u8 **)mgr;
    task = *(u8 **)(list + 4);
    if (task == NULL) {
        return (s32)list;
    }
    if (task[0] & 1) {
        return 1;
    }
    cls = *(u8 **)(task + 0x28);
    if (*(void **)cls != (void *)0x001A7FA0u) { /* PS2 address of EftStruggle_Update */
        return (s32)cls;
    }
    return func_00129C28(arg0, *(s32 *)(task + 0x38));
}
