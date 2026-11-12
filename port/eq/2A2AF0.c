#include "common.h"

extern u8 *D_003876A0;

s32 func_0028C648(void);
s32 func_002A0C10(void);
void func_002A1340(void);
void func_002A1590(s32 arg0);
void func_002A15D0(s32 arg0);
void func_002A1678(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_PrintAt(s32 arg0, s32 arg1, u8 *arg2);
void func_002A13E8(void);
s32 BattleSetup_FinishEx(s32 arg0);
u32 Font_GetHeight(u8 *arg0);
u8 *Dma_BeginDirect(void);
void Dma_EndDirect(u8 *arg0, s64 arg1);

void func_002A2AF0(void) {
    s32 s0;
    s32 s2;
    u8 *s1;
    u8 *p;
    s64 q;
    s32 h;

    s0 = func_0028C648();
    if (s0 == 0) {
        return;
    }
    s1 = *(u8 **)(D_003876A0 + 0x70);
    s2 = func_002A0C10();
    s1 = s1 + (((*(u32 *)(s1 + ((s0 + 0xB) * 4) - 4)) >> 2) << 2);
    s0 = Font_GetHeight(s1);

    p = Dma_BeginDirect();
    *(s64 *)(p + 0x00) = ((s64)0x10000000 << 32) | 0x8001;
    *(s64 *)(p + 0x08) = 0xE;
    *(s64 *)(p + 0x18) = 0x42;
    *(s64 *)(p + 0x10) = 0x44;
    *(s64 *)(p + 0x20) = ((s64)0x44000000 << 32) | 0x8001;
    *(s64 *)(p + 0x28) = 0x5510;
    *(s64 *)(p + 0x38) = (((s64)0x3F800000 << 16) | 0x6000) << 16;
    *(s64 *)(p + 0x30) = 0x46;
    q = (((((s64)0xFFFFFF << 16) | 0x8E00) << 16) | 0x9000);
    *(s64 *)(p + 0x40) = (((((s64)0xFFFFFF << 16) | 0x7200) << 16) | 0x7000);
    *(s64 *)(p + 0x48) = q;
    Dma_EndDirect(p + 0x50, q);

    func_002A1340();
    func_002A1590(1);
    func_002A15D0(1);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, 0x80);
    func_002A1678(0, 0, 0, 0x80);

    h = (s32)s0;
    h = (h + (s32)(((u32)h) >> 31)) >> 1;
    Font_PrintAt(0x100, 0xE0 - h, s1);
    func_002A13E8();
    BattleSetup_FinishEx(s2);
}
