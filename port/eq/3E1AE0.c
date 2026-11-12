#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
void EftShotFx_Update_2494A0(void *);
extern void *D_004279C8 __attribute__((section(".data")));

void func_003E1AE0(void) {
    s32 v;

    if (!(M2C_FIELD(D_004279C8, s32 *, 0xC0) & 1)) {
        v = M2C_FIELD(D_004279C8, s32 *, 0xC4) + 8;
    } else {
        v = M2C_FIELD(D_004279C8, s32 *, 0xC8) + 0xA;
    }
    M2C_FIELD(D_004279C8, s32 *, 0xBC) = v;
    if (M2C_FIELD(D_004279C8, s32 *, 0xBC) != 0x12) {
        func_2493C0(M2C_FIELD(D_004279C8, s32 *, 0xC), 0x36EF, 0x3B08, 0, v);
        return;
    }
    EftShotFx_Update_2494A0(D_004279C8);
}
