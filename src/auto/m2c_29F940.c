#include "m2c_macros.h"

M2C_UNK Gsc_DumpCommand(s32, void *);               /* extern */
extern void *gGscCurTask;

void Gsc_DumpCurrent(void) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(gGscCurTask, void **, 0x14);
    Gsc_DumpCommand(M2C_FIELD(gGscCurTask, s32 *, 0x18), temp_v1 + M2C_FIELD(temp_v1, s32 *, 4));
}
