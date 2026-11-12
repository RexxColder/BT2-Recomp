#include "common.h"

extern u8 D_0036DD90[] __attribute__((section(".data")));
extern u8 *gBtlCam;
extern s32 gBtlCamView;
extern s32 gEftStorm;
extern u8 *D_003876A0;

void *Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0);
void EftStorm_WrapRain(s32 arg0, s32 arg1, s32 arg2);
void Vu0Screen_StoreMtx(s32 arg0);
s32 func_001431C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(f32 farg0, s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
void sceVu0InversMatrix(s32 arg0, s32 arg1);
void sceVu0Normalize(s32 arg0, s32 arg1);

void func_00143558(void) {
    u8 sp[0x100];
    u8 *a3p;
    u8 *s4;
    s32 s7;
    s32 s2;
    s32 v;

    a3p = *(u8 **)(gBtlCam + 0x600);
    s7 = *(s32 *)(a3p + 0x250);
    *(s64 *)(sp + 0x40) = *(s64 *)(D_0036DD90 + 0);
    *(s64 *)(sp + 0x48) = *(s64 *)(D_0036DD90 + 8);
    memset(sp + 0x50, 0, 0x10);
    s2 = s7 * 0x10;
    *(f32 *)(sp + 0x54) = 100.0f;
    s4 = (u8 *)Dma_BeginDirect();
    *(s64 *)(s4 + 0x00) = ((s64)0x10000000 << 32) | 0x8001;
    *(s64 *)(s4 + 0x08) = 0xE;
    s4 += 0x10;
    *(s64 *)(s4 + 0x08) = 0x42;
    *(s64 *)(s4 + 0x00) = 0x44;
    s4 += 0x10;
    sceVu0InversMatrix((s32)(sp + 0x70), gBtlCamView);
    sceVu0ApplyMatrix((s32)(sp + 0x40), (s32)(sp + 0x70), (s32)(sp + 0x40));
    func_00312650((s32)(sp + 0x60), gEftStorm + s2 + 0x8ED0, (s32)(sp + 0xA0));
    func_00312638((s32)(sp + 0x50), (s32)(sp + 0x50), (s32)(sp + 0x60));
    sceVu0Normalize((s32)(sp + 0x50), (s32)(sp + 0x50));
    func_00312680(20.0f, (s32)(sp + 0x50), (s32)(sp + 0x50));
    func_003126C8(gEftStorm + s2 + 0x8ED0, (s32)(sp + 0xA0));
    Vu0Screen_StoreMtx((s32)sp);
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 2)) {
        EftStorm_WrapRain((s32)(sp + 0x40), gEftStorm + 0x86D0, 0x40);
        v = func_001431C0((s32)s4, (s32)sp, gEftStorm + 0x86D0, 0x40, (s32)(sp + 0x50));
    } else if (s7 != 0) {
        EftStorm_WrapRain((s32)(sp + 0x40), gEftStorm + 0x86D0, 0x20);
        v = func_001431C0((s32)s4, (s32)sp, gEftStorm + 0x86D0, 0x20, (s32)(sp + 0x50));
    } else {
        EftStorm_WrapRain((s32)(sp + 0x40), gEftStorm + 0x8AD0, 0x20);
        v = func_001431C0((s32)s4, (s32)sp, gEftStorm + 0x8AD0, 0x20, (s32)(sp + 0x50));
    }
    Dma_EndDirect(v);
}
