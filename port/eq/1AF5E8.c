#include "common.h"

#define FL(o) (*(f32 *)(arg0 + (o)))
#define U8F(o) (*(u8 *)(arg0 + (o)))

s32 func_001AF5E8(u8 *arg0) {
    u8 v1;
    s32 v0;
    s32 cond;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;

    v1 = U8F(0x53);
    if (v1 == 0) {
        goto L608;
    }
    if (v1 == 1) {
        v1 = U8F(0x54);
        goto L640;
    }
    v0 = U8F(0x58);
    goto L6A0;

L608:
    f0 = FL(0x48) - 1.0f;
    FL(0x48) = f0;
    if (f0 <= 0.0f) {
        FL(0x48) = 0.0f;
        U8F(0x58) = 1;
        U8F(0x53) = 1;
        v1 = U8F(0x54);
        goto L640;
    }
    v0 = U8F(0x58);
    goto L6A0;

L640:
    if ((v1 & 1) != 0) {
        v0 = U8F(0x58);
        goto L6A0;
    }
    f3 = 0.0f;
    f2 = FL(0x44);
    f0 = FL(0x38);
    f1 = f3 - f0;
    if (f2 != 0.0f) {
        f1 = f1 / (f2 * 30.0f);
    }
    /* L680 */
    FL(0x3C) = f1;
    FL(0x40) = f3;
    U8F(0x54) = (u8)(v1 | 1);
    U8F(0x53) = (u8)(U8F(0x53) + 1);
    v0 = U8F(0x58);
    goto L6A0;

L6A0:
    if (v0 == 0) {
        goto L778;
    }
    f0 = FL(0x24);
    f3 = FL(0x10) * f0;
    f2 = FL(0x14) * f0;
    f1 = FL(0x18) * f0;
    f3 = FL(0x0) + f3;
    f2 = FL(0x4) + f2;
    f1 = FL(0x8) + f1;
    f0 = f0 + f0 * FL(0x28);
    v1 = U8F(0x54);
    FL(0x0) = f3;
    FL(0x4) = f2;
    FL(0x8) = f1;
    FL(0x24) = f0;
    if ((v1 & 1) == 0) {
        goto L754;
    }
    f0 = FL(0x38);
    f1 = FL(0x3C);
    f0 = f0 + f1;
    FL(0x38) = f0;
    if (f1 > 0.0f) {
        f1 = FL(0x40);
        cond = (f1 < f0);
    } else {
        f1 = FL(0x40);
        cond = (f0 < f1);
    }
    if (cond) {
        FL(0x38) = f1;
        U8F(0x54) = (u8)(v1 & 0xFE);
    }
    f0 = FL(0x38);
    goto L758;

L754:
    f0 = FL(0x38);

L758:
    if (f0 <= 0.0f) {
        FL(0x38) = 0.0f;
        return 1;
    }
    return 0;

L778:
    return 0;
}
