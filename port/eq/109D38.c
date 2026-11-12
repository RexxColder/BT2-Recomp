#include "common.h"

s32 func_0025AB48(void);
void DemoCam_Stop(void);
void func_0027ABE8(f32 farg0);

void func_00109D38(void) {
    if (func_0025AB48() != 0) {
        DemoCam_Stop();
    }
    func_0027ABE8(1.0f);
}
