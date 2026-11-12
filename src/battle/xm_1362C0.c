#include "m2c_macros.h"

s32 EftStage_IsDrawOn(void);
void func_00136A00(void);
s32 func_00276D00(void);
extern void *gBtlStage;

// Stage draw-check: does nothing when bit 1 of gBtlStage+8 is set; otherwise calls func_00136A00 when the draw check passes and func_00276D00 returns 0.
void func_001362C0(void) {
    if (!(M2C_FIELD(gBtlStage, s32 *, 8) & 1)) {
        if (EftStage_IsDrawOn() != 0 && func_00276D00() == 0) {
            func_00136A00();
        }
    }
}
