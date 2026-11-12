#include "common.h"

void func_002EFA40(void *arg0, void *arg1);
void func_002EFAB8(void *arg0, s32 arg1);
void func_002FC550(s32 arg0);
s32 func_002FC860(void *arg0, s32 arg1);
void func_002FC8C8(s32 arg0);
void func_002FED70(void *arg0, void *arg1);
s64 func_0030B658(s32 arg0, void *arg1);
void *memset(void *, s32, u32);
extern u8 D_00356E98[] __attribute__((section(".data")));
extern s32 D_00356EA8 __attribute__((section(".data")));
extern u8 D_0037E678[] __attribute__((section(".data")));
extern u8 D_0037E6A0[] __attribute__((section(".data")));
extern u8 D_0037E6C0[] __attribute__((section(".data")));
extern u8 D_0037E6D8[] __attribute__((section(".data")));

s8 *func_002FF290(void *arg0, s32 arg1) {
    s32 sp[64];
    u8 *s5;
    u8 *s2;
    u8 *s1;
    s32 s0;
    s32 s3;
    s32 s4;
    s32 s6;
    s32 fp;
    s32 temp;

    s5 = (u8 *)arg0;
    s3 = 0;
    s6 = 0;
    fp = 0;
    memset(sp, 0, 0x100);
    s4 = (arg1 >= 0xE) ? 0xD : arg1;
    if (s4 > 0) {
        s2 = s5;
        do {
            temp = (*(s32 *)(D_00356E98 + 0xC) * s3) + s3;
            s3 += 1;
            s1 = s5 + ((*(s32 *)(D_00356E98 + 0x8) * 8) + temp);
            func_002FED70(s1, sp);
            if (*(s8 *)s1 != 0) {
                func_002FC550(0x6600);
                s0 = func_002FC860(sp, 1);
                func_002FC550(0x6601);
                if (s0 < 0) {
                    fp += 1;
                    func_002EFA40(D_0037E678, sp);
                } else {
                    *(s32 *)s2 = s0;
                    s6 += 1;
                    *(s32 *)(s2 + 4) = (s32)func_0030B658(s0, sp);
                    func_002EFA40(D_0037E6A0, s1);
                    func_002FC550(0x6800);
                    func_002FC8C8(s0);
                    func_002FC550(0x6801);
                    func_002FC550(0x6700);
                    func_002FC860(sp, D_00356EA8);
                    func_002FC550(0x6701);
                }
            }
            s2 += 8;
        } while (s3 < s4);
    }
    func_002EFA40(D_0037E6C0, (void *)(s32)s6);
    if (fp > 0) {
        func_002EFAB8(D_0037E6D8, 0xA);
    }
    return (s8 *)(s32)s6;
}
