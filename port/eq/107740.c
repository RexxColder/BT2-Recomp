#include "common.h"

s32 Dma_BeginDirect();
void Dma_EndDirect(s32 arg0);
s32 func_001070F8(s32 arg0, s32 arg1);
void func_00286D08(s32 arg0, s32 arg1, s32 arg2);
s32 func_002A0C10();
void BattleSetup_FinishEx(s32 arg0);
extern u8 *gObjOutline;

void func_00107740(void) {
    s32 s0;
    u8 *t;

    if (*(u8 *)(gObjOutline + 4) != 0 && *(s32 *)(gObjOutline + 0xC) != 0) {
        func_00286D08(*(s32 *)(gObjOutline + 0), 0x2A40, 0x2A00);
        s0 = func_002A0C10();
        t = (u8 *)Dma_BeginDirect();
        *(s64 *)(t + 0x00) = ((s64)0x10000000 << 32) | 0x8005;
        *(s64 *)(t + 0x08) = 0xE;
        *(s64 *)(t + 0x10) = 0x44;
        *(s64 *)(t + 0x18) = 0x42;
        *(s64 *)(t + 0x20) = 0x30000;
        *(s64 *)(t + 0x28) = 0x47;
        *(s64 *)(t + 0x30) = 0;
        *(s64 *)(t + 0x38) = 0x4A;
        *(s64 *)(t + 0x40) = ((s64)0x13100 << 16) | 0xE0;
        *(s64 *)(t + 0x48) = 0x4E;
        *(s64 *)(t + 0x50) = 5;
        *(s64 *)(t + 0x58) = 8;
        Dma_EndDirect(func_001070F8((s32)(t + 0x60), *(s32 *)(gObjOutline + 0xC)));
        BattleSetup_FinishEx(s0);
    }
}
