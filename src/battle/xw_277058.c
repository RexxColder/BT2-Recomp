#include "common.h"

s32 func_00276FD0(f32 arg0);

// Ends a battle-event interrupt; calls func_00276FD0 with the constant 0.25f (in $f12).
void BtlEvent_EndInterrupt(void) {
    func_00276FD0(0.25f);
}
