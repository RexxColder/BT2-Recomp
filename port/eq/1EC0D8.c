#include "common.h"

extern void *D_0038790C;

s32 BtlPool_InitSlot(void *arg0, s32 arg1, s32 arg2);
s32 Ot_Align64(s32 arg0);

void func_001EC0D8(void) {
    s32 s1;

    s1 = *(s32 *)((u8 *)D_0038790C + 0x60);
    if (*(s32 *)((u8 *)D_0038790C + 0x68) & 2) {
        s1 = BtlPool_InitSlot(D_0038790C, Ot_Align64(0xA000), s1);
    }
    if (*(s32 *)((u8 *)D_0038790C + 0x68) & 4) {
        s1 = BtlPool_InitSlot((u8 *)D_0038790C + 0x10, Ot_Align64(0x1F4000), s1);
    }
    if (*(s32 *)((u8 *)D_0038790C + 0x68) & 8) {
        s1 = BtlPool_InitSlot((u8 *)D_0038790C + 0x20, Ot_Align64(0x19000), s1);
    }
    if (*(s32 *)((u8 *)D_0038790C + 0x68) & 0x10) {
        s1 = BtlPool_InitSlot((u8 *)D_0038790C + 0x30, Ot_Align64(0x400), s1);
    }
    if (*(s32 *)((u8 *)D_0038790C + 0x68) & 0x20) {
        s1 = BtlPool_InitSlot((u8 *)D_0038790C + 0x40, Ot_Align64(0x400), s1);
        if (*(s32 *)((u8 *)D_0038790C + 0x68) & 0x20) {
            BtlPool_InitSlot((u8 *)D_0038790C + 0x50, Ot_Align64(0x400), s1);
        }
    }
}
