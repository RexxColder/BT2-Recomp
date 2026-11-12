#include "common.h"

void func_00262FB8(s32 arg0, s32 arg1, s32 arg2);
void BtlObjDraw_SetEnv();
void ObjGs_AddTexEnv(void);
void func_002644F0(s32 arg0, f32 farg0);
void func_002634F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);
s32 func_00264DA0(s32 arg0, s32 arg1);
s32 Vu1Pkt_LoadProg0();
void func_002629D0(s32 arg0, s32 arg1);
void func_00264540(s32 arg0, s32 arg1, s32 arg2, s64 arg3, s32 arg4, s32 arg5);
void func_00262AA8(s32 arg0, s32 arg1, s32 arg2);

/* 0x002651B8: draws arg1 records of the block at arg0 (64-byte records from +0xB00, the sub-block
 * base at +0xAF0). A non-zero low byte of arg2 runs func_00262FB8 first. Each record whose flag
 * bit 1 is set is drawn through func_002634F0 (with the float at +0xE58 and bit 21 of the flags),
 * then through func_00264DA0, func_002629D0, func_00264540 and func_00262AA8. The float argument of
 * func_002644F0 (used only when arg1 >= 2) is the incoming float parameter (GUESS). */
void func_002651B8(u8 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 a2m = arg2 & 0xFF;
    s32 s0 = 0;
    s32 s3 = 0;
    u8 *s1;
    s32 flags;

    if (a2m != 0) {
        func_00262FB8((s32)arg0, arg1, a2m);
    }
    BtlObjDraw_SetEnv();
    ObjGs_AddTexEnv();
    if (arg1 <= 0) {
        return;
    }

    s1 = arg0 + 0xB00;
    do {
        flags = *(s32 *)s1;
        if ((flags & 2) != 0) {
            if (arg1 >= 2) {
                func_002644F0(s3, farg0);
                flags = *(s32 *)s1;
            }
            func_002634F0((s32)arg0, (s32)(arg0 + 0xAF0), (s32)s1, (flags >> 21) & 1,
                          *(f32 *)(arg0 + 0xE58));
            BtlObjDraw_SetEnv();
            ObjGs_AddTexEnv();
            s0 = func_00264DA0((s32)arg0, (s32)s1);
            Vu1Pkt_LoadProg0();
            func_002629D0((s32)arg0, (s32)s1);
            func_00264540((s32)arg0, (s32)s1, 0, 0, s0, 0);
            func_00262AA8((s32)arg0, (s32)(arg0 + 0xAF0), (s32)s1);
        }
        s3++;
        s1 += 0x40;
    } while (s3 < arg1);
}
