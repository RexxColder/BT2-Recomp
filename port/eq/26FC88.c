#include "common.h"

s32 func_0026C9F0(s32 arg0, s32 arg1);
u8 *func_0026CA00(s32 arg0, s32 arg1);
s32 func_0026CC60(s32 arg0, s32 arg1);
s32 func_0026DE08(s32 arg0, s32 arg1, s32 arg2);
void func_0026FBD0(s32 arg0);
void Flash_CxformIdentity(s32 arg0);
u8 *func_0028BAA8(s32 arg0);
void memset(void *arg0, s32 arg1, s32 arg2);

s32 func_0026FC88(u8 *arg0, s32 *arg1) {
    s32 s0;
    s32 s1;
    s32 fp;
    s32 s4;
    s32 s6;
    s32 s7;
    s32 v;
    u8 *s2;
    u8 *p;
    u8 *e;

    s6 = 0;
    s7 = 0;
    s1 = func_0026C9F0(*arg1, 0);
    fp = s1 * 2;
    s2 = func_0026CA00(*arg1, 0);
    s0 = (fp + s1) << 6;
    p = func_0028BAA8(s0);
    *(u8 **)arg0 = p;
    memset(p, 0, s0);
    if (s1 > 0) {
        s4 = 0;
        do {
            v = *s2;
            s2 += 2;
            e = *(u8 **)arg0 + s4;
            s4 += 0xC0;
            *(u16 *)(e + 0x40) = (u16)v;
            *(s32 *)(e + 0x44) = 0;
            s6 += 1;
            memset(e + 0x48, 0, 0x60);
            func_0026FBD0((s32)(e + 0x78));
            Flash_CxformIdentity((s32)(e + 0x90));
            *(f32 *)(e + 0x54) = 1.0f;
            v = func_0026CC60(*arg1, *(u16 *)(e + 0x40));
            s7 += func_0026DE08((s32)arg1, (s32)(e + 0xA8), v);
        } while (s6 < s1);
    }
    *(s32 *)(arg0 + 4) = s1;
    return s7 + ((fp + s1) << 6);
}
