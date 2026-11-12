#include "common.h"

#define F(p, off) (*(f32 *)((u8 *)(p) + (off)))

void func_00269A40(void *arg0, s32 arg1, void *arg2);
void *func_00269A08(void *arg0, s32 arg1);

void func_0025E638(void *arg0, void *arg1, void *arg2) {
    u8 *s1, *a2, *v0, *vp;
    f32 f20, f1, f2, f3;
    s32 s0, a1v, a0v, v1;

    a2 = arg2;
    s1 = *(u8 **)((u8 *)arg0 + 0x48);
    f20 = F(*(u8 **)((u8 *)arg0 + 0x958), 0x40) / F(*(u8 **)((u8 *)arg1 + 0x958), 0x40);
loop:
    s0 = *(u16 *)(s1 + 0xA);
    if (s0 < 0x47) {
        func_00269A40(arg0, s0, a2);
        a2 = func_00269A08(arg1, s0);
        if (a2 != NULL) {
            a1v = *(s32 *)((u8 *)arg0 + 0xBF8);
            a0v = *(u16 *)((u8 *)(s32)a1v + 6 + s0 * 2);
            if (a0v != 0) {
                v0 = (u8 *)(s32)(a1v + a0v * 4);
                if ((*(u16 *)v0 & 1) == 0) {
                    v1 = *(u16 *)(v0 + 2);
                    vp = v0 + 4;
                    if (v1 != 0) {
                        do {
                            v1 -= 1;
                            f2 = F(vp, 0) - F(a2, 0x30);
                            F(vp, 0) = f2;
                            f1 = F(vp, 4) - F(a2, 0x34);
                            f1 = f1 * f20;
                            f3 = F(vp, 8) - F(a2, 0x38);
                            F(vp, 4) = f1;
                            F(vp, 8) = f3;
                            F(vp, 0) = f2 + F(s1, 0x30);
                            F(vp, 4) = f1 + F(s1, 0x34);
                            F(vp, 8) = f3 + F(s1, 0x38);
                            vp += 0x18;
                        } while (v1 != 0);
                    }
                }
            }
        }
    }
    if (*(u16 *)(s1 + 6) == 0) {
        s1 += *(s32 *)s1;
        goto loop;
    }
}
