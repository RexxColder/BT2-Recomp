#include "common.h"

u8 *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent();
void BtlTask_SetDead(s32 arg0, u32 arg1, u8 *arg2);
void EftTexSet_Load32(u8 *arg0, u8 *arg1, u8 *arg2);
void *memset(void *arg0, s32 arg1, s32 arg2);
extern u8 *gEftDust;
extern u8 *D_003876A0;

void func_0013C308(s32 arg0) {
    u8 *obj;
    u32 a1;

    if (gEftDust == NULL) {
        gEftDust = BtlPool_Alloc(BtlPool_GetCurrent(arg0), 0x2C0);
        memset(gEftDust, 0, 0x2C0);
    }
    if (*(u8 **)(gEftDust + 0x00) == NULL) {
        *(u8 **)(gEftDust + 0x00) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x18);
        memset(*(u8 **)(gEftDust + 0x00), 0, 0x18);
    }
    if (*(u8 **)(gEftDust + 0x04) == NULL) {
        *(u8 **)(gEftDust + 0x04) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x280);
        memset(*(u8 **)(gEftDust + 0x04), 0, 0x280);
    }
    if (*(u8 **)(gEftDust + 0x08) == NULL) {
        *(u8 **)(gEftDust + 0x08) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x21C);
        memset(*(u8 **)(gEftDust + 0x08), 0, 0x21C);
    }
    if (*(u8 **)(gEftDust + 0x0C) == NULL) {
        *(u8 **)(gEftDust + 0x0C) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x1A40);
        memset(*(u8 **)(gEftDust + 0x0C), 0, 0x1A40);
    }
    if (*(u8 **)(gEftDust + 0x10) == NULL) {
        *(u8 **)(gEftDust + 0x10) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x960);
        memset(*(u8 **)(gEftDust + 0x10), 0, 0x960);
    }
    if (*(u8 **)(gEftDust + 0x14) == NULL) {
        *(u8 **)(gEftDust + 0x14) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x10E0);
        memset(*(u8 **)(gEftDust + 0x14), 0, 0x10E0);
    }
    if (*(u8 **)(gEftDust + 0x18) == NULL) {
        *(u8 **)(gEftDust + 0x18) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x12C0);
        memset(*(u8 **)(gEftDust + 0x18), 0, 0x12C0);
    }

    obj = *(u8 **)(D_003876A0 + 0x04);
    if ((*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) != 0) {
        obj = obj + 0x40;
    }
    a1 = *(u32 *)(obj + 0x48);
    if (*(u32 *)(obj + 0x4C) != a1) {
        EftTexSet_Load32(gEftDust + 0xB0, obj + ((a1 >> 2) * 4), obj);
        return;
    }
    BtlTask_SetDead(arg0, a1, obj);
}
