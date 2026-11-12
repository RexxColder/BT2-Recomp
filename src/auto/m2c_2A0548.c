#include "m2c_macros.h"

M2C_UNK List_PushBack(M2C_UNK *, s32);              /* extern */
M2C_UNK List_Remove(M2C_UNK *, s32);                /* extern */
extern M2C_UNK D_003B0F30 __attribute__((section(".data")));
extern M2C_UNK gGscTaskList __attribute__((section(".data")));

void Gsc_FreeTask(s32 arg0) {
    List_Remove(&gGscTaskList, arg0);
    List_PushBack(&D_003B0F30, arg0);
}
