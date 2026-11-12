#include "common.h"

extern u8 *D_00421C94;
extern u8 *D_00387F2C;
extern char D_00421DA8[], D_00421DB0[], D_00421DC0[], D_00421DD0[], D_00421DE8[], D_00421DF8[];
extern char D_00421E08[], D_00421E20[], D_00421E38[], D_00421E50[], D_00421E60[], D_00421E70[], D_00421E80[];
void func_0026EBC0();
void func_0026ED60(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, f32 f12, f32 f13);
void func_00249FB8();
void func_002495A8();
void func_00249778();
s32 func_00325830();
void func_00249BB8();
void func_00249DB8();
void func_0026EFC8();
void func_0026EEC8();
void func_0026EC48();
void func_0026EF38(s32 a0, s32 a1, f32 f12, f32 f13);
void func_0026EA58();
s32 BattleSetup_Finish();

#define O D_00421C94
#define OW(off) (*(s32 *)(O + (off)))

s32 func_003BED00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp[0x28];
    s32 *rect = sp + 4;
    s32 *name = sp + 12;
    s32 s1, i, s0, s3, s2;
    f32 f0;
    u32 k1 = 0x433B851E, k2 = 0x3FE10623;
    f32 c187 = *(f32 *)&k1, c176 = *(f32 *)&k2;

    sp[6] = 0x200;
    sp[7] = 0x100;
    sp[4] = 0;
    sp[5] = 0;
    s1 = (s32)(O + 0x448);
    func_0026EBC0(s1, D_00421DA8, sp, 0x100, arg4);
    func_0026ED60(s1, (s32)sp, (s32)rect, (s32)(O + 0x538), 0, -0.25f, 0.0f);
    s1 = (s32)(O + 0x470);
    func_0026EBC0(s1, D_00421DB0, sp);
    func_00249FB8(s1, sp, 0, 0, OW(8), OW(0x534), 1);
    if (OW(0x52C) & 4) {
        func_0026EBC0(s1, D_00421DC0, sp);
        func_002495A8(s1, sp, O + 0x544, 1);
        func_0026EBC0(s1, D_00421DD0, sp);
        func_00249778(s1, sp, O + 0x548, 3);
    } else {
        func_0026EBC0(s1, D_00421DE8, sp);
        func_002495A8(s1, sp, O + 0x53C, 1);
        func_0026EBC0(s1, D_00421DF8, sp);
        func_00249778(s1, sp, O + 0x540, 3);
    }
    i = 0;
    do {
        u8 *rec;
        func_00325830(name, D_00421E08, i);
        func_0026EBC0(s1, name, sp);
        rec = D_00387F2C + (OW(0x524) + i) * 34;
        if (*(u16 *)(rec + 0x1DFC) & 1) {
            func_00249BB8(s1, sp, 0, 0, OW(0x10), *(s16 *)(rec + 0x1DF8), 0);
        }
        func_0026EFC8(s1, sp, 4);
        func_00325830(name, D_00421E20, i);
        func_0026EBC0(s1, name, sp);
        rec = D_00387F2C + (OW(0x524) + i) * 34;
        i++;
        if (*(u16 *)(rec + 0x1DFC) & 1) {
            func_00249DB8(s1, sp, 0, 0, OW(0x14), *(s16 *)(rec + 0x1DF8), 0);
        }
        func_0026EFC8(s1, sp, 4);
    } while (i < 3);
    func_0026EBC0(s1, D_00421E38, sp);
    func_0026EEC8(s1, sp, 0, (OW(0x520) - OW(0x524)) * 58);
    func_0026EBC0(s1, D_00421E50, sp);
    func_0026EFC8(s1, sp, 8);
    func_0026EBC0(s1, D_00421E60, sp);
    if (OW(0x524) > 0) {
        func_0026EFC8(s1, sp, 4);
    } else {
        func_0026EFC8(s1, sp, 8);
    }
    sp[6] = 0x40;
    sp[7] = 0x20;
    sp[4] = 0x20;
    sp[5] = 0;
    func_0026EBC0(s1, D_00421E70, sp);
    func_0026EC48(s1, sp, rect);
    if (OW(0x524) < 7) {
        func_0026EFC8(s1, sp, 4);
    } else {
        func_0026EFC8(s1, sp, 8);
    }
    f0 = (f32)OW(0x524) * c187;
    f0 = f0 / 10.0f;
    s0 = (s32)f0;
    if (f0 >= 2147483648.0f) {
        s0 = (s32)(f0 - 2147483648.0f) | (s32)0x80000000;
    }
    func_0026EBC0(s1, D_00421E80, sp);
    func_0026EF38(s1, (s32)sp, 1.0f, c176);
    func_0026EEC8(s1, sp, 0, s0);
    s3 = 0;
    s2 = 1;
    do {
        s2--;
        func_0026EA58(O + s3 + 0x448);
        s3 += 0x28;
    } while (s2 >= 0);
    return BattleSetup_Finish();
}
