#include "m2c_macros.h"

s32 func_1018B8(s32);
void EftShotFx_Update_2494A0(void *);
void func_243A80(s32, s32, s32);
extern s32 D_003B0C34 __attribute__((section(".data")));
extern void *D_0042FD78 __attribute__((section(".data")));

void func_00421158(s32 arg0) {
    if (D_003B0C34 & 0x4000) {
        if (func_1018B8(arg0) != 5) {
            M2C_FIELD(D_0042FD78, s32 *, 0xB4) |= 0x10;
            EftShotFx_Update_2494A0(D_0042FD78);
        }
    } else if (D_003B0C34 & 8) {
        func_243A80(0, 0, 0);
    }
}
