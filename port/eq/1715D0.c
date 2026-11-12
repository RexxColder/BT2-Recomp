#include "common.h"

extern f32 D_003848C4;

void Mtx_StoreIdentity(f32 *arg0);
void func_00129C28(void *arg0, void *arg1);
s32 func_001F42D8(s32 arg0);
void func_00208F18(s32 arg0, f32 *arg1, s32 arg2);
void func_00208DE8(s32 arg0, f32 *arg1, s32 arg2);
void func_00171738(f32 arg0, s32 arg1, f32 *arg2, s32 arg3, s32 arg4, s32 arg5);

void func_001715D0(u8 *arg0) {
    f32 buf[20];
    f32 *sp = buf;
    f32 *tmp = buf + 4;
    u8 *s3;
    s32 s2;
    s32 cnt;

    s3 = *(u8 **)(arg0 + 0xB0);
    s2 = func_001F42D8(*(s32 *)s3);
    cnt = *(s32 *)(arg0 + 0xAB4) + 1;
    *(s32 *)(arg0 + 0xAB4) = cnt;
    if (**(s32 **)(s3 + 0x20) != 0x175) {
        return;
    }
    if (cnt == 0x71) {
        Mtx_StoreIdentity(tmp);
        func_00208F18(s2, tmp, 0x11);
        func_00208DE8(s2, sp, 0x11);
        sp[0] = sp[0] + sp[12] * 100.0f;
        sp[1] = sp[1] + sp[13] * 100.0f;
        sp[2] = sp[2] - sp[14] * 100.0f;
        sp[3] = 1.0f;
        func_00129C28(arg0 + 0x80, sp);
    }
    if (*(s32 *)(arg0 + 0xAB4) >= 0xEA) {
        func_00129C28(arg0 + 0x80, arg0 + 0x70);
    }
    if (*(s32 *)(arg0 + 0xAB4) == 0x45) {
        sp[0] = 256.0f;
        sp[1] = 224.0f;
        *(s32 *)&sp[2] = 0;
        sp[3] = 1.0f;
        func_00171738(D_003848C4, *(s32 *)s3, sp, 0, 0, 1);
    }
}
