#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387A40;

void func_00100E78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BtlScene_Reset(s32 arg0);
void func_0028BB60(s32 arg0);
void func_002A85B0(void);
void func_001048F0(s32 arg0, s32 arg1);
void func_00104150(s32 arg0);
void func_002998D8(void);
void func_00271FD8(s32 arg0);
void func_00262330(s32 arg0, s32 arg1, s32 arg2);
void func_001F5A98(void);
void func_0011E6C0(void);
void func_0025BE48(void);
s32 func_0025A310(void);
void func_00280BC0(void);
void func_00105570(void);
void func_002422C8(void);
void StgRigid_Reset(void);
void func_00284AC8(void);
void func_00101F60(void);

void func_00102640(void) {
    u8 *g;
    s32 s2;
    s32 i;
    s32 off;
    u8 *a3p;
    s32 a0v;
    s32 v1v;
    s32 a1val;
    s32 vv;
    s32 flag;
    s32 skip;

    s2 = 0;
    g = D_003876A0;
    *(s64 *)(g + 0x4D8) &= ~((s64)0xB900);
    func_00100E78((s32)g, -0x801, -0x1001, -0x2001);
    BtlScene_Reset(0);
    if (*(s32 *)(g + 0x2C) != 0) {
        func_0028BB60(*(s32 *)(g + 0x2C));
        *(s32 *)(g + 0x2C) = 0;
    }
    func_002A85B0();

    for (i = 0; i < 2; i++) {
        off = 464 * i;
        a3p = g + off;
        a0v = *(s32 *)(a3p + 0x2AC);
        v1v = *(s32 *)(a3p + 0x2A8);
        skip = 0;
        if (v1v == a0v) {
            vv = *(s32 *)D_00387A40;
            if (*(u8 *)((s32)(i * 0x18580 + vv) + 0xE5C) == 0) {
                if ((*(s32 *)(g + 0x4E0) << ((1 << i) & 31)) == 0) {
                    skip = 1;
                }
            }
        }
        if (skip) {
            continue;
        }
        a1val = *(s32 *)(a3p + 0x2A8);
        s2 = s2 | (1 << ((i + 1) & 31));
        func_001048F0(i, a1val);
        *(s32 *)(a3p + 0x2AC) = *(s32 *)(a3p + 0x2A8);
    }

    if (*(s32 *)(g + 0xCC) != *(s32 *)(g + 0xD4)) {
        s2 = s2 | 1;
        func_00104150(*(s32 *)(g + 0xCC));
        *(s32 *)(g + 0xD4) = *(s32 *)(g + 0xCC);
    }
    flag = s2 & 1;
    if (s2 != 0) {
        func_002998D8();
        flag = s2 & 1;
    }
    if (flag == 0) {
        func_00271FD8(0);
    }
    func_00262330(0, 0, 0);
    func_00262330(0, 1, 1);
    func_001F5A98();
    func_0011E6C0();
    func_0025BE48();
    func_0025A310();
    BtlScene_Reset(s2 != 0);
    func_00280BC0();
    func_00105570();
    func_002422C8();
    StgRigid_Reset();
    func_002A85B0();
    func_00284AC8();
    func_00101F60();
}
