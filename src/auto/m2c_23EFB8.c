#include "m2c_macros.h"

s32 *Battle_GetSetup();                             /* extern */

s32 BattleResult_GetFlags(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return *Battle_GetSetup(r_a0);
}
