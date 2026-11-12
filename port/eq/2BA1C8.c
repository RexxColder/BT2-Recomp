#include "common.h"

typedef s32 (*FnGet)(s32, s32);
typedef void (*FnSet4)(s32, s32, s32, s32);
typedef void (*FnSet3)(s32, s32, s32);
typedef void (*FnCall1)(s32);

s32 func_003063E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void memcpy(void *arg0, void *arg1, s32 arg2);
void func_002BA420(s32 arg0, s32 arg1);
extern u8 D_003798A8[] __attribute__((section(".data")));
extern u8 D_003798B0[] __attribute__((section(".data")));

void func_002BA1C8(u8 *arg0) {
    s32 sp[12];
    u8 *s1;
    u8 *s2;
    u8 *vt;
    s32 r;
    s32 ok;

    s1 = arg0 + 0x194;
    s2 = *(u8 **)(arg0 + 0x17C);
    vt = *(u8 **)s2;
    r = ((FnGet)(*(s32 *)(vt + 0x24)))((s32)s2, 1);

    ok = 0;
    if (r != 0) {
        sp[0] = *(s32 *)(arg0 + 0x180);
        sp[1] = r;
        ok = func_003063E8((s32)sp, (s32)D_003798A8, (s32)D_003798B0, (s32)&sp[4]);
    }
    if (ok == 0) {
        *(s32 *)(s1 + 4) = 0;
        *(s32 *)(s1 + 0) = 1;
        *(s32 *)(s1 + 8) = 0;
        return;
    }
    if (*(s32 *)(arg0 + 0x188) != 0) {
        memcpy((void *)*(s32 *)(arg0 + 0x188), (void *)sp[4], sp[5]);
        *(s32 *)(s1 + 0) = 1;
        *(s32 *)(s1 + 4) = *(s32 *)(arg0 + 0x188);
        *(s32 *)(s1 + 8) = sp[5];
        vt = *(u8 **)s2;
        ((FnSet4)(*(s32 *)(vt + 0x18)))((s32)s2, 1, 0x7FFFFFFF, (s32)&sp[8]);
        vt = *(u8 **)s2;
        ((FnSet3)(*(s32 *)(vt + 0x20)))((s32)s2, 0, (s32)&sp[8]);
        vt = *(u8 **)s2;
        ((FnCall1)(*(s32 *)(vt + 0x14)))((s32)s2);
        return;
    }
    *(s32 *)(s1 + 0) = 1;
    *(s32 *)(s1 + 4) = sp[4];
    *(s32 *)(s1 + 8) = sp[5];
    func_002BA420((s32)arg0, sp[5]);
}
