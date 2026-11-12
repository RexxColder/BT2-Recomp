#include "common.h"

void DemoCam_FixupAnim(s32 arg0);
s32 sceVu0UnitMatrix(s32 arg0);
extern u8 *D_00387A30;

void DemoCam_SetAnim(s32 arg0) {
    *(s32 *)(D_00387A30 + 0x2B0) = arg0;
    DemoCam_FixupAnim(*(s32 *)(D_00387A30 + 0x2B0));
    *(s32 *)(D_00387A30 + 0x2E8) = 0;
    *(s32 *)(D_00387A30 + 0x2EC) = 0;
    *(s32 *)(D_00387A30 + 0x2F0) = 0;
    *(s32 *)(D_00387A30 + 0x2F4) = 0;
    sceVu0UnitMatrix((s32)(D_00387A30 + 0x250));
}
