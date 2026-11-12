#include "common.h"

void BattleSide_SetChara(u8 *arg0, s32 arg1);
s32 BtlObjXf_Update(u8 *arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_00211270(void);
u8 *func_00211288(s32 arg0);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211688(u8 *arg0, s32 arg1);
void func_00211D80(u8 *arg0, s32 arg1);
void func_0025F2A0(s32 arg0);
void func_00260D48(s32 arg0);

void func_001F6B00(void) {
    s32 s1;
    s32 idx;
    s32 n;
    u8 *v;

    s1 = 0;
    for (;;) {
        n = func_00211270();
        if (s1 >= n) {
            break;
        }
        idx = s1;
        s1 += 1;
        v = func_00211288(idx);
        memset(v + 0x510, 0, 0x2A0);
        func_00211D80(v, 0);
        *(s32 *)(v + 0xC00) = 1;
        *(s32 *)(v + 0xC08) = -1;
        *(s32 *)(v + 0xC0C) = -1;
        *(s32 *)(v + 0xAC4) = 0;
        func_002113C0(v, 0, 2, 0);
        func_002113C0(v, 0, 4, 1);
        memset(v + 0x13C, 0, 0x14);
        func_00211688(v, 1);
        if ((func_001FA3A8(BtlObjXf_Update(v)) & 0x10) || (*(s32 *)(v + 0xB48) >= 3)) {
            func_002113C0(v, 9, 0x02000000, 1);
        }
        *(s32 *)(v + 0xB48) = 1;
        BattleSide_SetChara(v, 0);
        func_0025F2A0(*(s32 *)(v + 0x1530));
        func_00260D48(*(s32 *)(v + 0x1530));
    }
}
