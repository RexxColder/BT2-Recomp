#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 func_00126460(s32 arg0);
s32 func_00126580(void);
void EftTexSet_Load8(u8 *arg0, s32 arg1);
void EftTexSet_Load16(u8 *arg0, s32 arg1);
void EftTexSet_Load32(u8 *arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

extern u8 *D_00387840;
extern s32 D_00387844;

void func_001A9E20(s32 arg0) {
    u8 *s0;
    u8 *s2;
    u8 *s2b;
    s32 v;

    D_00387840 = (u8 *)BtlPool_Alloc(BtlPool_GetCurrent(), 0x1098);
    memset(D_00387840, 0, 0x1098);
    FLD(D_00387840, 0) = func_00126580();
    s0 = D_00387840;
    s2 = s0 + 0x10;
    FLD(s0, 8) = func_00126460(0x37);
    v = func_00126460(0x3E);
    FLD(s0, 0x10) = v;
    EftTexSet_Load8(s0 + 0x18, v);
    FLD(s2, 0x98) = func_00126460(0x3F);
    FLD(s2, 0x9C) = func_00126460(0x40);
    v = func_00126460(0x3B);
    FLD(s2, 0x1C0) = v;
    EftTexSet_Load16(s0 + 0x1D8, v);
    FLD(s2, 0x2D8) = func_00126460(0x3C);
    FLD(s2, 0x2DC) = func_00126460(0x3D);
    v = func_00126460(0x4E);
    FLD(s0, 0x2F0) = v;
    EftTexSet_Load32(s0 + 0x2F8, v);
    FLD(s0, 0x720) = func_00126460(0x4F);
    v = func_00126460(0x50);
    FLD(s0, 0x508) = v;
    EftTexSet_Load32(s0 + 0x510, v);
    FLD(s0, 0x724) = func_00126460(0x51);
    v = func_00126460(0x38);
    FLD(s2, 0x720) = v;
    EftTexSet_Load16(s0 + 0x738, v);
    FLD(s2, 0x838) = func_00126460(0x39);
    FLD(s2, 0x83C) = func_00126460(0x3A);
    s2b = s0 + 0x850;
    v = func_00126460(0x47);
    FLD(s0, 0x850) = v;
    EftTexSet_Load8(s0 + 0x858, v);
    FLD(s2b, 0x98) = func_00126460(0x48);
    FLD(s2b, 0x9C) = func_00126460(0x49);
    v = func_00126460(0x44);
    FLD(s2b, 0x1C0) = v;
    EftTexSet_Load16(s0 + 0xA18, v);
    FLD(s2b, 0x2D8) = func_00126460(0x45);
    FLD(s2b, 0x2DC) = func_00126460(0x46);
    v = func_00126460(0x4A);
    FLD(s0, 0xB30) = v;
    EftTexSet_Load32(s0 + 0xB38, v);
    FLD(s0, 0xF60) = func_00126460(0x4B);
    v = func_00126460(0x4C);
    FLD(s0, 0xD48) = v;
    EftTexSet_Load32(s0 + 0xD50, v);
    FLD(s0, 0xF64) = func_00126460(0x4D);
    v = func_00126460(0x41);
    FLD(s2b, 0x720) = v;
    EftTexSet_Load16(s0 + 0xF78, v);
    FLD(s2b, 0x838) = func_00126460(0x42);
    FLD(s2b, 0x83C) = func_00126460(0x43);
    D_00387844 = BtlTask_CreateChildList(arg0, FLD(D_00387840, 0) * 4, 0x60);
}
