#include "common.h"

s32 func_00211270(void);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0020A658(s32 arg0);
s32 func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
void func_00312680(void *arg0, void *arg1, f32 farg0);
void func_00312638(s32 arg0, s32 arg1, void *arg2);
s32 BtlChar_GetPos(s32 arg0);
void func_00211688(s32 arg0, s32 arg1);
void func_00260D48(s32 arg0);
s32 func_002115D0(s32 arg0);

s32 func_0020DEA0(s32 arg0) {
    u8 v14[16];
    u8 v15[16];
    u8 v16[16];
    s32 i;
    s32 s0;
    s32 s2;
    s32 s3;
    s32 v7;
    s32 pos1;
    s32 pos2;
    u8 *o2;
    u8 *o3;

    i = 0;
    s2 = 0;
    s3 = 0;
    while (i < func_00211270()) {
        if (func_0020A658(i) == 0) {
            s0 = func_00211288(i);
            func_002113C0(s0, 1, 0x200, 0);
            if (func_00211310(s0, 5, 0x20) != 0) {
                s3 = s0;
            }
            if (func_00211310(s0, 6, 2) != 0) {
                s2 = s0;
            }
        }
        i++;
    }

    if (s3 == 0 || s2 == 0 || s3 == s2) {
        return 0;
    }

    o2 = (u8 *)s2;
    o3 = (u8 *)s3;
    v7 = *(s32 *)(*(s32 *)(o2 + 0x1530) + 0xD80);
    func_00208DE8(*(s32 *)(o3 + 0x1534), v14, 0x34);
    func_00208DE8(*(s32 *)(o2 + 0x1534), v15, v7);

    if (func_00211310(s3, 7, 0x100) != 0) {
        func_00312650(v16, v15, v14);
        if (func_00211310(s2, 2, 0x200) != 0) {
            func_00312680(v16, v16, 1.0f - *(f32 *)((u8 *)*(s32 *)(o2 + 0x1530) + 0xBEC));
        }
        pos1 = BtlChar_GetPos(s3);
        pos2 = BtlChar_GetPos(s3);
        func_00312638(pos1, pos2, v16);
        func_00211688(s3, 0);
        func_00260D48(*(s32 *)(o3 + 0x1530));
        return func_002115D0(s3);
    } else {
        func_00312650(v16, v14, v15);
        if (func_00211310(s2, 2, 0x200) != 0) {
            func_00312680(v16, v16, 1.0f - *(f32 *)((u8 *)*(s32 *)(o2 + 0x1530) + 0xBEC));
        }
        pos1 = BtlChar_GetPos(s2);
        pos2 = BtlChar_GetPos(s2);
        func_00312638(pos1, pos2, v16);
        func_00211688(s2, 0);
        func_00260D48(*(s32 *)(o2 + 0x1530));
        func_002115D0(s2);
        return func_002113C0(s2, 1, 0x200, 1);
    }
}
