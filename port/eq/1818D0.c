#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
void *memcpy(void *arg0, const void *arg1, u32 arg2);
void func_00180398(u8 *arg0, s32 arg1);
void func_00181A20(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x001818D0(obj, src): s0 = obj->+0x38; clear 0xC0 bytes at s0; copy src[0..0xF] to s0+0x80, src+0x10 to s0+0x90,
 * 1.0f to s0+0xB0; func_00180398(s0, src->+0x10); then tail-call func_00181A20(s0, p, p->+0x2D0, src->+4,
 * src[0]) with p = src->+0xC. */
void func_001818D0(u8 *arg0, u8 *arg1) {
    u8 *s0 = *(u8 **)(arg0 + 0x38);
    u8 *p;

    memset(s0, 0, 0xC0);
    memcpy(s0 + 0x80, arg1, 0x10);
    *(s32 *)(s0 + 0x90) = *(s32 *)(arg1 + 0x10);
    *(f32 *)(s0 + 0xB0) = 1.0f;
    func_00180398(s0, *(s32 *)(arg1 + 0x10));
    p = *(u8 **)(arg1 + 0xC);
    func_00181A20(s0, p, *(s32 *)(p + 0x2D0), *(s32 *)(arg1 + 4), *(u8 *)arg1);
}
