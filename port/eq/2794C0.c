#include "common.h"

extern u8 *D_003876A0;
extern s32 D_003B0A84 __attribute__((section(".data")));

s32 func_00271370(void);
void Dma_AddData(u8 *arg0, s32 arg1);
void Dma_AddFrame(s32 arg0, s32 arg1, s32 arg2);
void StgPanBlur_CopyScreen(void);
void StgPanBlur_RestoreEnv(void);
s32 func_002796E8(u8 *arg0);
void func_00279C60(u8 *arg0, s32 arg1);
void func_002814D0(s32 arg0, s32 arg1, s64 arg2, s64 arg3);

void func_002794C0(u8 *arg0) {
    s32 var_s1;
    s32 var_s2;
    s64 flags;

    var_s1 = 1;
    flags = *(s64 *)(D_003876A0 + 0x4D8);
    var_s2 = 1;
    if (flags & 2) {
        if (!(flags & 0x100)) {
            var_s1 = func_002796E8(arg0 + 0x4C0);
            var_s2 = func_002796E8(arg0 + 0x5D0);
        }
        if ((var_s1 != 0) || (var_s2 != 0)) {
            Dma_AddData(arg0 + 0x494, 0x10);
            func_00271370();
            Dma_AddFrame((D_003B0A84 & 1) ? 0 : 0x70, 8, 0xFFFFFF);
            func_002814D0(0, 0x1C00, *(u16 *)(arg0 + 0x4B4), 0x44);
            StgPanBlur_CopyScreen();
            if (var_s1 != 0) {
                func_00279C60(arg0 + 0x4C0, arg0[0x6E0]);
            }
            if (var_s2 != 0) {
                func_00279C60(arg0 + 0x5D0, arg0[0x6E0]);
            }
            StgPanBlur_RestoreEnv();
        }
    } else {
        if (!(flags & 0x100)) {
            var_s1 = func_002796E8(arg0 + 0x4C0);
        }
        if (var_s1 != 0) {
            Dma_AddData(arg0 + 0x494, 0x10);
            func_00271370();
            Dma_AddFrame((D_003B0A84 & 1) ? 0 : 0x70, 8, 0xFFFFFF);
            func_002814D0(0, 0x1C00, *(u16 *)(arg0 + 0x4B4), 0x44);
            StgPanBlur_CopyScreen();
            func_00279C60(arg0 + 0x4C0, arg0[0x6E0]);
            StgPanBlur_RestoreEnv();
        }
    }
}
