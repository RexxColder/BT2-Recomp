#include "common.h"

extern u8 *D_00387AEC;
extern f32 D_003870AC;
extern f32 D_003870B0;
extern f32 D_003870B4;
extern f32 D_003870B8;
extern f32 D_003870BC;

u8 *func_0027AC38(void);
s32 func_00126560(void);
void func_003126C8(u8 *arg0, s32 arg1);
s32 rand(void);

s32 func_0027BCC0(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4) {
    u8 *s0;
    f32 *s1;
    s32 cnt;
    s32 ret;
    s32 r;
    s32 v1;
    f32 f20;
    f32 f;

    if (D_00387AEC == NULL) {
        return 0;
    }
    s0 = func_0027AC38();
    if (s0 == NULL) {
        return 0;
    }
    s1 = (f32 *)(s0 + 0x28);
    *(s32 *)s0 = *(s32 *)s0 | 1;
    cnt = 0x13;
    ret = func_00126560();

    v1 = ((ret ^ 1) != 0) ? arg0 : 0;
    *(s32 *)(s0 + 0x4) = v1;
    *(f32 *)(s0 + 0x8) = farg0 * 30.0f;
    func_003126C8(s0 + 0x440, arg1);
    *(f32 *)(s0 + 0xC) = farg1;

    *(f32 *)(s0 + 0x20) = D_003870B8;
    *(f32 *)(s0 + 0x24) = D_003870BC;
    *(f32 *)(s0 + 0x18) = farg2;
    *(f32 *)(s0 + 0x10) = farg3;
    *(f32 *)(s0 + 0x14) = -((farg3 * D_003870B0) / *(f32 *)(s0 + 0x8));
    *(f32 *)(s0 + 0x1C) = (farg2 * D_003870B4) / *(f32 *)(s0 + 0x8);
    f20 = 0.5f - (farg4 * 0.5f);

    do {
        r = rand();
        f = (f32)r;
        f = f / D_003870AC;
        f = f * farg4;
        f = f20 + f;
        *s1 = f;
        s1++;
        cnt--;
    } while (cnt >= 0);

    if (arg0 != 0) {
        *(s32 *)(D_00387AEC + 0xAC) = *(s32 *)(D_00387AEC + 0xAC) + 1;
    } else {
        *(s32 *)(D_00387AEC + 0xA8) = *(s32 *)(D_00387AEC + 0xA8) + 1;
    }
    return 1;
}
