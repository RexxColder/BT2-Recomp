#include "common.h"

extern u8 *D_0038790C;
void func_0028BB60(s32 arg0);

void func_001EBE68(void) {
    if (*(s32 *)(D_0038790C + 0x60) != 0) {
        func_0028BB60(*(s32 *)(D_0038790C + 0x60));
        *(s32 *)(D_0038790C + 0x60) = 0;
    }
    if (D_0038790C != 0) {
        func_0028BB60((s32)D_0038790C);
        D_0038790C = 0;
    }
}
