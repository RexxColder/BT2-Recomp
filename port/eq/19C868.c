#include "common.h"

void BtlTask_SetDead(u8 *arg0);
s32 func_00126528(void);
void func_00152608(s32 arg0, u8 *arg1, s32 arg2);
void func_0019CCD8(u8 *arg0);
s32 func_0020A540(s32 arg0);
void func_0019CFA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00151FB0(u8 *arg0);
s32 func_00152200(s32 arg0, u8 *arg1);
void func_00152930(s32 arg0, u8 *arg1);
void func_0019D0F8(u8 *arg0);
void func_0019D240(u8 *arg0);
void func_0019D390(u8 *arg0);

void func_0019C868(u8 *arg0) {
    u8 *st;
    s32 temp_s0;
    s32 s3;
    u32 a0;
    s32 need;
    u8 temp_v1;

    s3 = 0;
    st = *(u8 **)(arg0 + 0x38);
    temp_s0 = func_00126528();
    a0 = *(u16 *)(st + 0xC24);
    if (!(a0 & 0x40)) {
        a0 = *(u16 *)(st + 0xC24);
        if (func_0020A540(*(s32 *)(st + 0xC1C)) != 0) {
            if (!(a0 & 4)) {
                *(u16 *)(st + 0xC24) = (u16)(a0 | 4);
                a0 = a0 | 4;
            }
        }
    }

    if (temp_s0 == 0) {
        if (a0 & 0x40) {
            func_00152608(*(s32 *)(st + 4), st + 0x840, *(s32 *)(st + 0xC20));
        }
        temp_v1 = arg0[1];
        if (temp_v1 == 1) {
            a0 = *(u16 *)(st + 0xC24);
            if (a0 & 4) {
                arg0[1] = 2;
                a0 = *(u16 *)(st + 0xC24);
            }
        } else if (temp_v1 < 2) {
            if (temp_v1 == 0) {
                arg0[1] = 1;
            }
            a0 = *(u16 *)(st + 0xC24);
        } else if (temp_v1 == 2) {
            a0 = *(u16 *)(st + 0xC24) | 8;
            *(u16 *)(st + 0xC24) = (u16)a0;
        } else {
            a0 = *(u16 *)(st + 0xC24);
        }

        /* L954: decide whether the flag path calls func_0019CCD8 */
        need = 0;
        if ((a0 & 0x40) == 0) {
            need = 1;
        } else if (*(s32 *)(st + 4) != 0) {
            u8 *o4 = *(u8 **)(st + 4);
            if (!(*(u32 *)(*(u8 **)(o4 + 0x20) + 0x30) & 2)) {
                need = 1;
            }
        }
        if (need) {
            func_0019CCD8(st);
            a0 = *(u16 *)(st + 0xC24);
        }

        /* L994 */
        if ((a0 & 4) == 0) {
            if ((a0 & 0x40) == 0) {
                if (a0 & 0x200) {
                    func_0019D0F8(arg0);
                    a0 = *(u16 *)(st + 0xC24);
                }
            } else {
                func_00152930(*(s32 *)st, st + 0x90);
                a0 = *(u16 *)(st + 0xC24);
                if (a0 & 0x200) {
                    func_0019D240(arg0);
                    a0 = *(u16 *)(st + 0xC24);
                }
            }
        }
    }

    /* L9E8 */
    if (a0 & 0x40) {
        func_0019CFA0(arg0, *(s32 *)st, *(s32 *)(st + 0xC1C), 0);
        func_00151FB0(st + 0x90);
        s3 = func_00152200(*(s32 *)st, st + 0x90) != 0;
    }

    /* L9CA1C */
    func_0019D390(st);
    if ((s3 == 0) && (*(u16 *)(st + 0xC24) & 8)) {
        BtlTask_SetDead(arg0);
    }
}
