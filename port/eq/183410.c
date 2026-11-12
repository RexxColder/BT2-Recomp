#include "common.h"

#define F(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define H(p, off) (*(u16 *)((u8 *)(p) + (off)))

f32 sinf(f32 farg0);
f32 EftMath_WrapAngle(f32 farg0);
void func_00183DE0(s32 arg0, s32 arg1, f32 farg0);
void func_0012D5D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
void func_00129C28(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);

extern f32 D_00384B70;
extern f32 D_00384B74;
extern f32 D_00384B78;
extern f32 D_00384B7C;
extern f32 D_00384B80;
extern f32 D_00384B84;

void func_00183410(u8 *arg0) {
    u8 sp[0x30];
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *s4;
    f32 s;
    f32 w;
    f32 nw;

    s4 = arg0 + 0xA10;

    if (!(H(arg0, 0xAD6) & 0x100)) {
        if (H(arg0, 0xAD6) & 4) {
            F(arg0, 0xA74) = F(arg0, 0xA74) + (sinf(F(arg0, 0xB10)) * D_00384B70);
            F(arg0, 0xB10) = EftMath_WrapAngle(F(arg0, 0xB10) + D_00384B70);
            func_00183DE0((s32)(arg0 + 0xA90), W(s4, 0x30), D_00384B74);
        }
        if (H(arg0, 0xAD6) & 8) {
            s = sinf(F(arg0, 0xB14)) * D_00384B78;
            F(arg0, 0xA78) = F(arg0, 0xA78) - (F(arg0, 0xA98) * s);
            F(arg0, 0xA70) = F(arg0, 0xA70) - (F(arg0, 0xA90) * s);
            F(arg0, 0xA74) = F(arg0, 0xA74) - (F(arg0, 0xA94) * s);
            F(arg0, 0xB14) = EftMath_WrapAngle(F(arg0, 0xB14) + D_00384B7C);
        }
        if (H(arg0, 0xAD6) & 2) {
            w = F(arg0, 0xB1C);
            nw = w + (w * F(arg0, 0xB18));
            F(arg0, 0xA70) = F(arg0, 0xA70) + (F(arg0, 0xAC0) * w);
            F(arg0, 0xA78) = F(arg0, 0xA78) + (F(arg0, 0xAC8) * w);
            F(arg0, 0xA74) = (F(arg0, 0xA74) + (F(arg0, 0xAC4) * w)) - D_00384B80;
            F(arg0, 0xB1C) = nw;
            func_00183DE0((s32)(arg0 + 0xA90), W(s4, 0x30), nw * D_00384B84);
        }
        func_00129C28((s32)(arg0 + 0xAB0), (s32)(arg0 + 0xA70));
        return;
    }

    s1 = arg0 + 0xA90;
    s3 = arg0 + 0xA70;
    func_0012D5D8((s32)sp, (s32)s3, (s32)s1, W(s4, 0x30), F(s4, 0x20), F(s4, 0x24));
    func_00129C28((s32)s1, (s32)sp);
    if (H(arg0, 0xAD6) & 0x200) {
        func_00129C28((s32)(arg0 + 0xA80), (s32)s3);
    }
    s0 = sp + 0x10;
    func_00129BD0((s32)s0, (s32)s1, F(s4, 0x20));
    Vec3_Add((s32)s3, (s32)s3, (s32)s0);
    H(arg0, 0xAD6) = (u16)(H(arg0, 0xAD6) | 0x200);

    func_0012D5D8((s32)sp, (s32)s3, (s32)s1, W(s4, 0x30), F(s4, 0x20), F(s4, 0x24));
    s1 = sp + 0x20;
    func_00129C28((s32)s1, (s32)sp);
    func_00129BD0((s32)s0, (s32)s1, F(s4, 0x20));
    Vec3_Add((s32)(arg0 + 0xAB0), (s32)s3, (s32)s0);
}
