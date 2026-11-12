#include "m2c_macros.h"

s32 Gsc_FindFile();                                 /* extern */
M2C_UNK Gsc_FreeFile(s32);                          /* extern */

void BtlChars_OnModelLoaded(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    s32 temp_v0;

    temp_v0 = Gsc_FindFile(r_a0);
    if (temp_v0 != 0) {
        Gsc_FreeFile(temp_v0);
    }
}
