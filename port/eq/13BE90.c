#include "common.h"

#define PTR(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern u8 *D_003876A0;
extern u8 *gEftDust;
extern f32 D_00384370;
extern f32 D_00384374;

s32 rand(void);
s32 func_00126560(void);
s32 func_00276AC8();
s32 func_0013B350(f32 *out);
void func_0013B408(s32 arg0, void *arg1);
void func_0013B458(f32 farg0, s32 arg0, void *arg1, s32 arg2);
u8 func_00141CC8(s32 arg0);
s32 func_00210000(void *arg0, s32 arg1);
void func_003126C8(void *arg0, void *arg1);
void func_00312638(void *arg0, void *arg1, void *arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
void sceVu0Normalize(void *arg0, void *arg1);
void EftUtil_ClipSegToWater(void *arg0, void *arg1, void *arg2);

void func_0013BE90(void *arg0) {
    f32 vA[4];
    f32 vB[4];
    f32 vC[4];
    f32 vD[4];
    f32 t40;
    f32 f20;
    f32 f21;
    f32 f0;
    u8 *p60;
    u8 *p64;
    u8 *ap;
    u8 *s0;
    s32 kop;
    s32 tp;
    s32 ty;

    t40 = 0.0f;
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    if (gEftDust == NULL) {
        return;
    }
    if (W(arg0, 0x50) & 8) {
        return;
    }
    p60 = PTR(arg0, 0x60);
    if (W(p60, 4) & 4) {
        return;
    }
    if (W(p60, 4) & 0x400) {
        return;
    }

    func_0013B350(&t40);
    if (func_00126560() == 0) {
        if (func_00276AC8(vA) == 0xC) {
            t40 += 5.0f;
        }
    }
    func_003126C8(vA, arg0 + 0x20);
    func_003126C8(vB, arg0 + 0x30);

    p60 = PTR(arg0, 0x60);
    if (W(p60, 4) & 1) {
        func_00312650(vC, vB, vA);
        sceVu0Normalize(vC, vC);
        f0 = *(f32 *)((u8 *)arg0 + 0x78);
        vC[0] = vC[0] * f0;
        vC[1] = vC[1] * f0;
        vC[2] = vC[2] * f0;
        vC[3] = 1.0f;
        func_00312638(vB, PTR(arg0, 0x60) + 0x10, vC);
        func_003126C8(vA, PTR(arg0, 0x60) + 0x10);
        p60 = PTR(arg0, 0x60);
        W(p60, 4) = W(p60, 4) | 0x400;
    }

    f20 = vA[1] - vB[1];
    if (20.0f < f20) {
        f20 = 20.0f;
    }
    f21 = (f20 * D_00384370) + ((((f32)rand() / D_00384374) * 3.0f) - 1.5f);

    if (t40 <= vA[1] && vB[1] <= t40) {
        EftUtil_ClipSegToWater(vD, vA, vB);
        kop = 0x3C;
        goto clip_tail;
    }
    if (!(vA[1] <= t40) || !(t40 <= vB[1])) {
        goto c240;
    }
    EftUtil_ClipSegToWater(vD, vA, vB);
    kop = 0x3D;

clip_tail:
    if (W(arg0, 0xC) == 0) {
        func_0013B458(f21, W(arg0, 0), vD, 1);
        func_00210000(vD, kop);
        return;
    }
    p64 = PTR(arg0, 0x64);
    if (p64 == NULL) {
        return;
    }
    ap = PTR(p64, 0x20);
    tp = W(ap, 8);
    if (tp == 3) {
        goto x1;
    }
    ty = W(ap, 0);
    if (ty == 0x10E || ty == 0x10F || ty == 0x110 || ty == 0x111 || ty == 0x154 || ty == 0x155) {
        goto x1;
    }
    func_0013B458(f20, W(arg0, 0), vD, 2);
    return;

x1:
    if (W(arg0, 0) != 0) {
        s0 = gEftDust + 0x6D;
    } else {
        s0 = gEftDust + 0x6C;
    }
    if (*s0 != 0) {
        *s0 = *s0 - 1;
        return;
    }
    func_0013B458(f20, W(arg0, 0), vD, 2);
    ap = PTR(PTR(arg0, 0x64), 0x20);
    *s0 = func_00141CC8(W(ap, 0));
    return;

c240:
    if (W(arg0, 0xC) == 0) {
        return;
    }
    if (func_00276AC8() == 0xA) {
        if (t40 < vA[1] && vA[1] < t40 + 12.0f) {
            func_0013B408(W(arg0, 0), arg0);
        }
        return;
    }
    if (t40 - 6.0f < vA[1] && vA[1] < t40 + 12.0f) {
        func_0013B408(W(arg0, 0), arg0);
    }
}
