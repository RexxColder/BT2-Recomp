#include "m2c_macros.h"

void BtlPool_Free(s32, void *);
s32 BtlPool_GetCurrent(void);
void BtlPool_Reset(s32);
void BtlPool_SetCurrent(s32);
void func_00148A80(s32, s32, s32);
extern void *D_00387760;

// Tears down the effect pool: frees the two blocks held in D_00387760, resets pools 3..5, and for slots 0..4 calls func_00148A80 for kinds 0 and 1.
void func_001481B8(void) {
    s32 var_s0;

    BtlPool_SetCurrent(3);
    BtlPool_Free(BtlPool_GetCurrent(), M2C_FIELD(D_00387760, void **, 4));
    BtlPool_Free(BtlPool_GetCurrent(), D_00387760);
    D_00387760 = NULL;
    BtlPool_Reset(3);
    BtlPool_Reset(4);
    BtlPool_Reset(5);
    for (var_s0 = 0; var_s0 < 5; var_s0++) {
        func_00148A80(0, var_s0, 0);
        func_00148A80(1, var_s0, 0);
    }
}
