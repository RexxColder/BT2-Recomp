#include "common.h"

extern u8 *gEftTechEvt;

s32 func_0020AB90(s32 arg0);
s32 BtlCharApi_IsInTechnique(s32 arg0);
s32 func_0020A758(s32 arg0);
s32 BtlCharApi_ObjTestAttr(s32 arg0, s32 arg1);
void BtlTask_SetDead(s32 arg0, s32 arg1);

void EftTechEvtTask_UpdateRush(u8 *arg0) {
    u8 *s1;
    s32 *ps0;
    s32 *ps;
    u8 *base;
    s32 k;

    s1 = *(u8 **)(arg0 + 0x38);
    ps0 = *(s32 **)s1;
    if (func_0020AB90(*ps0) != 0) {
        *(s32 *)(s1 + 0x10) = *(s32 *)(s1 + 0x10) | 8;
    }
    if (*(s32 *)(s1 + 0x10) & 8) {
        *(s32 *)(s1 + 0x14) = *(s32 *)(s1 + 0x14) + 1;
    }
    if (BtlCharApi_IsInTechnique(*ps0) != 0) {
        if (!(*(s32 *)(s1 + 0x10) & 8) || func_0020A758(*ps0) != 0) {
            if (BtlCharApi_ObjTestAttr(*ps0, 0x800) != 0) {
                base = *(u8 **)(gEftTechEvt + 4);
                ps = (s32 *)(base + *ps0 * 16);
                *ps = *ps | 8;
                BtlTask_SetDead((s32)arg0, (s32)base);
                return;
            }
            for (k = 0; k < *(s32 *)(gEftTechEvt + 8); k++) {
                base = *(u8 **)(gEftTechEvt + 4);
                ps = (s32 *)(base + k * 16);
                if (BtlCharApi_ObjTestAttr(k, 0x200) != 0) {
                    *ps = *ps | 2;
                    *(s32 *)(s1 + 0x10) = *(s32 *)(s1 + 0x10) | 2;
                }
                if (BtlCharApi_ObjTestAttr(k, 0x400) != 0) {
                    *ps = *ps | 4;
                    *(s32 *)(s1 + 0x10) = *(s32 *)(s1 + 0x10) | 4;
                }
                if (BtlCharApi_ObjTestAttr(k, 0x1000) != 0) {
                    *ps = *ps | 0x10;
                }
                if (BtlCharApi_ObjTestAttr(k, 0x2000) != 0) {
                    *ps = *ps | 0x20;
                }
                if (BtlCharApi_ObjTestAttr(k, 0x4000) != 0) {
                    *ps = *ps | 0x40;
                }
            }
            return;
        }
        base = *(u8 **)(gEftTechEvt + 4);
        ps = (s32 *)(base + *ps0 * 16);
        *ps = *ps | 0x80;
        BtlTask_SetDead((s32)arg0, (s32)base);
        return;
    }
    base = *(u8 **)(gEftTechEvt + 4);
    ps = (s32 *)(base + *ps0 * 16);
    *ps = *ps | 0x80;
    BtlTask_SetDead((s32)arg0, (s32)base);
}
