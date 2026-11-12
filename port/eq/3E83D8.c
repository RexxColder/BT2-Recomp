#include "m2c_macros.h"

void func_2493C0(s32, s32, s32, s32, s32);
extern void *D_004279D4 __attribute__((section(".data")));

void func_003E83D8(void) {
    s32 a0v;
    s32 v1;
    s32 v0;

    a0v = M2C_FIELD(D_004279D4, s32 *, 0xC8);
    if ((a0v & 0x1F) == 0) {
        v1 = M2C_FIELD(D_004279D4, s32 *, 0xCC);
        if ((u32)v1 < 6) {
            switch (v1) {
                case 0:
                    v0 = 0x1C;
                    break;
                case 1:
                    v0 = 0x1D;
                    break;
                case 2:
                    v0 = 0x1E;
                    break;
                case 3:
                    v0 = 0x20;
                    break;
                case 4:
                    v0 = 0x21;
                    break;
                default:
                    v0 = 0xC;
                    break;
            }
            M2C_FIELD(D_004279D4, s32 *, 0xC4) = v0;
        }
    } else if (a0v & 4) {
        M2C_FIELD(D_004279D4, s32 *, 0xC4) = 0x1F;
    }
    func_2493C0(M2C_FIELD(D_004279D4, s32 *, 0xC), 0x36EF, 0x3B08, 0, M2C_FIELD(D_004279D4, s32 *, 0xC4));
}
