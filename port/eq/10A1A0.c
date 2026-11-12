#include "common.h"

void func_0027ABE8(f32 farg0);
void DemoCam_Stop(void);
void func_0020CE20(s32 arg0);

s32 func_0010A1A0(u8 *arg0) {
    func_0027ABE8(1.0f);
    DemoCam_Stop();
    func_0020CE20(*(u8 *)(arg0 + 9));
    func_0020CE20(*(u8 *)(arg0 + 0xA));
    return 1;
}
