#include "common.h"

/* 0x00280988: Dma_AddData(a0 + 0x494, 0x10); func_00271370(); h = *(u16 *)(a0 + 0x4B4);
   tail func_002814D0(0, 0x1C00, h, *(u8 *)(a0 + 0x5A2) ? 0x48 : 0x44). */
void Dma_AddData(s32 arg0, s32 arg1);
s32 func_00271370(void);
void func_002814D0(s32 arg0, s32 arg1, s64 arg2, s64 arg3);

void func_00280988(s32 a0) {
    u16 h;
    s32 flag;

    Dma_AddData(a0 + 0x494, 0x10);
    func_00271370();
    flag = *(u8 *)((u8 *)a0 + 0x5A2);
    h = *(u16 *)((u8 *)a0 + 0x4B4);
    if (flag != 0) {
        func_002814D0(0, 0x1C00, h, 0x48);
        return;
    }
    func_002814D0(0, 0x1C00, h, 0x44);
}
