#include "common.h"

void BtlObjDraw_SetEnv(void *arg0, void *arg1, s32 arg2, s32 arg3);
void ObjGs_AddTexEnv(void);
void func_002634F0(f32 farg0, void *arg0, void *arg1, void *arg2, s32 arg3);
s32 func_00264DA0(void *arg0, void *arg1);
void Vu1Pkt_LoadProg0(void);
void func_002629D0(void *arg0, void *arg1);
void func_00264540(void *arg0, void *arg1, s32 arg2, s64 arg3, s32 arg4, s32 arg5);
void func_00262AA8(void *arg0, void *arg1, void *arg2);

/* 0x002652E8: for the object block at arg0 + 0x40*arg1 with flags word at +0xB00 (bit 0x2): BtlObjDraw_SetEnv(arg0,
 * block, arg2, arg3), ObjGs_AddTexEnv, func_002634F0(f32 at arg0+0xE58, arg0, arg0+0xAF0, block+0xB00, bit 21 of
 * the flags word), then BtlObjDraw_SetEnv() and ObjGs_AddTexEnv() again (no arguments), s0 = func_00264DA0(arg0,
 * block+0xB00), Vu1Pkt_LoadProg0(), func_002629D0(arg0, block+0xB00), func_00264540(arg0, block+0xB00, 0, 0, s0, 0),
 * and finally func_00262AA8(arg0, arg0+0xAF0, block+0xB00). */
void func_002652E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_a1;
    u8 *temp_s2;
    u8 *temp_s3;
    s32 temp_s0;

    temp_a1 = arg0 + (arg1 << 6);
    temp_s2 = temp_a1 + 0xB00;
    temp_s3 = arg0 + 0xAF0;
    if (*(s32 *)temp_s2 & 2) {
        BtlObjDraw_SetEnv(arg0, temp_a1, arg2, arg3);
        ObjGs_AddTexEnv();
        func_002634F0(*(f32 *)(arg0 + 0xE58), arg0, temp_s3, temp_s2, (*(s32 *)temp_s2 >> 21) & 1);
        ((void (*)(void))BtlObjDraw_SetEnv)();
        ObjGs_AddTexEnv();
        temp_s0 = func_00264DA0(arg0, temp_s2);
        Vu1Pkt_LoadProg0();
        func_002629D0(arg0, temp_s2);
        func_00264540(arg0, temp_s2, 0, 0, temp_s0, 0);
        func_00262AA8(arg0, temp_s3, temp_s2);
    }
}
