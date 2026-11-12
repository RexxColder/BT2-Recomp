#include "common.h"

extern u8 *D_003876A0;
s32 func_00207298(void *arg0, s32 arg1);

#define FLD(o) (*(s32 *)(arg0 + (o)))

void func_00207340(u8 *arg0) {
    u8 *tbl;
    s32 a0v;
    s32 a1v;
    s32 a2v;
    s32 v1v;
    s32 orv;

    memset(arg0 + 0x58, 0, 0x84);
    tbl = D_003876A0 + FLD(0x1534) * 0x1D0;
    if (tbl[0x2A4] != 0) {
        FLD(0x58) = 0x8000;
        FLD(0x5C) = 0x1000;
        FLD(0x60) = 0x2000;
        FLD(0x64) = 0x4000;
        FLD(0x68) = 0x800;
        FLD(0x6C) = 0x200;
        FLD(0x70) = 0x400;
        FLD(0x74) = 0x100;
    } else {
        FLD(0x58) = func_00207298(arg0, 0);
        FLD(0x5C) = func_00207298(arg0, 3);
        FLD(0x60) = func_00207298(arg0, 2);
        FLD(0x64) = func_00207298(arg0, 1);
        FLD(0x68) = func_00207298(arg0, 6);
        FLD(0x6C) = func_00207298(arg0, 7);
        FLD(0x70) = func_00207298(arg0, 4);
        FLD(0x74) = func_00207298(arg0, 5);
    }

    a1v = FLD(0x88) | 0x10000 | 0x10;
    FLD(0x78) = 0x05000000;
    FLD(0x80) = 0x0500FF00;
    FLD(0x84) = 0xF000;
    FLD(0xB8) = 0x2000;
    FLD(0xBC) = 0x4000;
    FLD(0xC4) = 0x8000;
    FLD(0xC0) = 0x1000;
    FLD(0xC8) = 2;
    FLD(0xCC) = 4;
    FLD(0xD0) = 0xF0000;
    FLD(0xD4) = 0xF00000;
    FLD(0xD8) = 1;
    a2v = FLD(0x8C) | 0x20000 | 0x40;
    a0v = FLD(0x90) | 0x40000 | 0x80;
    v1v = FLD(0x94) | 0x80000 | 0x20;
    FLD(0x7C) = 4;
    FLD(0x8C) = a2v;
    FLD(0x90) = a0v;
    FLD(0x94) = v1v;
    FLD(0x88) = a1v;
    if (!(a1v & 0x10000)) {
        FLD(0x98) = 0x10000;
    }

    if (!(a2v & 0x20000)) {
        FLD(0x9C) = 0x20000;
    }
    if (!(a0v & 0x40000)) {
        FLD(0xA0) = 0x40000;
    }
    if (!(v1v & 0x80000)) {
        FLD(0xA4) = 0x80000;
    }

    if (!(a1v & 0x10)) {
        FLD(0x98) = 0x10;
    }
    if (!(a2v & 0x40)) {
        FLD(0x9C) = 0x40;
    }
    if (!(a0v & 0x80)) {
        FLD(0xA0) = 0x80;
    }
    if (!(v1v & 0x20)) {
        FLD(0xA4) = 0x20;
    }

    orv = a1v | a2v | a0v | v1v | FLD(0x60) | FLD(0x64) | FLD(0x68) | FLD(0x6C) | FLD(0xD8);
    FLD(0x54) = orv;
    FLD(0xA8) = 0x100000;
    FLD(0xAC) = 0x200000;
    FLD(0xB0) = 0x400000;
    FLD(0xB4) = 0x800000;
}
