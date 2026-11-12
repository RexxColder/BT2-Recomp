#include "common.h"

extern f32 D_00385640;
extern f32 D_00385644;
extern f32 D_00385648;
extern f32 D_0038564C;
extern f32 D_00385650;
extern f32 D_00385654;
extern f32 D_00385658;
extern f32 D_0038565C;

s32 func_0020B1C0(void *a0);
void func_003126C8(void *a0, void *a1);
void func_00312650(void *a0, void *a1, void *a2);
f32 func_001DF2B0(void *a0);
void EftBlade_Spline(f32 f12, void *a0, void *a1);

#define SELF_S32(o) (*(s32 *)(self + (o)))
#define TAGS(i) (*(s32 *)(self + 0x1080 + ((i) << 2)))
#define GRP(C, CODE)                                                  \
    do {                                                              \
        u8 *g = self + (s2 << 4);                                     \
        EftBlade_Spline((C), g, self + 0x1000);                       \
        EftBlade_Spline((C), g + 0x800, self + 0x1040);               \
        TAGS(s2) = (CODE);                                            \
        s2 = (s2 + 1) & 0x7F;                                         \
        if (s2 == s3) {                                               \
            s3 = (s3 + 1) & 0x7F;                                     \
        }                                                             \
    } while (0)

void func_001DE408(u8 *self, u8 *fp, u8 *arg2, u8 *a3) {
    u8 sp[0x30] __attribute__((aligned(8)));
    u8 *s5 = a3;
    u8 *g;
    s32 s2;
    s32 s3;
    s32 s6;
    s32 s7;
    s32 s34;
    s32 s38;
    s32 v;
    s32 v1st;
    s32 k;
    f32 f;

    s2 = SELF_S32(0x1290);
    s3 = SELF_S32(0x128C);
    s34 = (s2 + 0x7C) & 0x7F;
    s38 = (s2 + 0x7D) & 0x7F;
    s6 = (s2 + 0x7E) & 0x7F;
    s7 = (s2 + 0x7F) & 0x7F;

    v = func_0020B1C0(s5);
    if (*(u8 *)(self + 0x1294) != v && *(u8 *)(self + 0x1294) == 0) {
        for (k = 0; k < 4; k++) {
            func_003126C8(self + 16 * k + 0x1000, fp);
            func_003126C8(self + 16 * k + 0x1040, arg2);
        }
    }

    v1st = func_0020B1C0(s5);
    *(u8 *)(self + 0x1294) = (u8)v1st;
    v = func_0020B1C0(s5);
    if (v != 0) {
        for (k = 0; k < 3; k++) {
            func_003126C8(self + 16 * k + 0x1000, self + 16 * k + 0x1010);
            func_003126C8(self + 16 * k + 0x1040, self + 16 * k + 0x1050);
        }
        func_003126C8(self + 0x1030, fp);
        func_003126C8(self + 0x1070, arg2);
    }

    /* L52C */
    if (s2 == s3 || s7 == s3 || s6 == s3 || s38 == s3 || s34 == s3) {
        goto L554;
    }
    goto L598;

L554:
    v = func_0020B1C0(s5);
    if (v == 0) {
        goto L948;
    }
    g = self + (s2 << 4);
    func_003126C8(g, fp);
    func_003126C8(g + 0x800, arg2);
    TAGS(s2) = 0x51;
    goto L934;

L598:
    v = func_0020B1C0(s5);
    if (v == 0) {
        goto L948;
    }
    func_00312650(sp + 0x20, self + 0x1030, self + 0x1020);
    f = func_001DF2B0(sp + 0x20);
    if (f <= 1.0f) {
        goto L908;
    }

    /* far path: one special pair at s7, then groups from s2 */
    g = self + (s7 << 4);
    func_003126C8(sp + 0x00, g);
    func_003126C8(sp + 0x10, g + 0x800);
    EftBlade_Spline(D_00385640, g, self + 0x1000);
    EftBlade_Spline(D_00385640, g + 0x800, self + 0x1040);
    TAGS(s7) = 0x4C;

    GRP(D_00385644, 0x4E);
    GRP(D_00385648, 0x50);
    GRP(D_0038564C, 0x52);
    GRP(0.5f, 0x54);
    GRP(D_00385650, 0x56);
    GRP(D_00385654, 0x58);
    GRP(D_00385658, 0x5A);
    GRP(D_0038565C, 0x5C);

    g = self + (s2 << 4);
    func_003126C8(g, sp + 0x00);
    func_003126C8(g + 0x800, sp + 0x10);
    TAGS(s2) = 0x5E;
    s2 = (s2 + 1) & 0x7F;
    if (s2 == s3) {
        s3 = (s3 + 1) & 0x7F;
    }
    /* L904 falls into L908 */

L908:
    g = self + (s2 << 4);
    func_003126C8(g, fp);
    func_003126C8(g + 0x800, arg2);
    TAGS(s2) = 0x60;
    goto L934;

L934:
    s2 = (s2 + 1) & 0x7F;
    if (s2 == s3) {
        s3 = (s3 + 1) & 0x7F;
    }

L948:
    SELF_S32(0x128C) = s3;
    SELF_S32(0x1290) = s2;
}
