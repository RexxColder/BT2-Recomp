#include "common.h"

extern u8 *gScrWarp;
extern u8 *D_00387A40;

s32 BtlStage_IsReady(void);
void StgRigid_GetMatrix(u8 *a0, s32 a1);
void func_00260B58(u8 *a0, u8 *a1);
f32 func_00273048(void);
void func_00242188(u8 *a0);
s32 func_00242040(u8 *a0);
void func_00242218(u8 *a0, s32 a1);

/* 0x002423F8: scripted warp step. Needs gScrWarp in state 1; sets a flag word at
 * base + idx*0x18580 + 0xAF0 chosen by a jump table (cases 0..10). */
void func_002423F8(void) {
    u8 *scr;
    s32 idx;
    s32 v;
    s32 flag;
    u8 *q;

    scr = gScrWarp;
    if (scr == NULL) {
        return;
    }
    if (*(s32 *)(scr + 0x40) != 1) {
        return;
    }
    if (BtlStage_IsReady() == 0) {
        func_00242188(scr + 0x40);
        return;
    }
    StgRigid_GetMatrix(scr + 0x60, *(s32 *)(scr + 0x4C));
    idx = *(s32 *)(scr + 0x48);
    if (idx >= 0x10) {
        return;
    }
    func_00260B58(*(u8 **)(D_00387A40 + 8) + idx * 0x1520, scr + 0x60);
    if (func_00273048() + 20.0f < *(f32 *)(scr + 0x94)) {
        func_00242188(scr + 0x40);
        return;
    }
    idx = func_00242040(scr + 0x40);
    if (idx < 0) {
        return;
    }
    v = *(s32 *)(scr + 0x50) - 1;
    if ((u32)v < 0xB) {
        flag = 0;
        switch (v) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            flag = 0x200;
            break;
        case 7:
            flag = 0x400;
            break;
        case 8:
            flag = 0x800;
            break;
        case 9:
            flag = 0x1000;
            break;
        case 10:
            flag = 0x2000;
            break;
        default:
            break;
        }
        q = *(u8 **)D_00387A40 + idx * 0x18580;
        *(s32 *)(q + 0xAF0) = *(s32 *)(q + 0xAF0) | flag;
    }
    func_00242218(scr + 0x40, idx);
}
