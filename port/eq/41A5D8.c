#include "common.h"

extern u8 *D_0042BB80 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

void func_00419110(s32 a0);
void func_00419040(void);
void func_00243968(s32 a0, s32 a1, s32 a2);
void func_00243A80(s32 a0, s32 a1, s32 a2);
void func_00419F68(s32 *a0);
void func_003B46D0(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_00271610(s32 a0, s32 a1);
void func_002438E8(void);
void func_00419E80(void);
void func_00419820(void);
void func_002437E8(void);
void func_003B4718(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_00101498(void);
s64 GetTimerSystemTime(void);
void func_00325370(s64 a0);
s32 rand(void);
s32 func_0024AF50(s32 a0);
void func_00101A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1);
void func_004197B0(void);
void func_0028B218(void);

/* 0x0041A5D8: outer fade/draw loop on the object at D_0042BB80. Runs until ColorFade reports done;
   then, if the flag stayed set, picks a random table entry (+0x140 pairs, count +0x144 / +0x13C),
   calls 101A60 with the state from D_00387F2C, and returns the flag. */
s32 func_0041A5D8(s32 a0) {
    s32 flag;
    s32 s0;
    s32 s3;
    s32 s5;
    s32 s6;
    s32 r;
    s32 e8;
    s32 cs;
    s32 t1v;
    u8 *A;
    u8 *h;
    u8 *slot;

    flag = 1;
    s3 = -1;
    func_00419110(a0);
    func_00419040();
    func_00243968(0, 0, 0);

    for (;;) {
        for (;;) {
            func_003B46D0();
            func_0028B090();
            func_0028BDA0();
            func_00297978();
            func_00271610(0x700, 0x720);
            func_002438E8();
            func_00419E80();
            func_00419820();
            func_002437E8();
            func_003B4718();
            if (!ColorFade_IsFadingOut()) {
                break;
            }
            func_00101498();
        }
        if (ColorFade_IsOutDone()) {
            break;
        }
        if (*(s32 *)(D_0042BB80 + 0xD0) & 2) {
            e8 = *(s32 *)(D_0042BB80 + 0xE8) - 1;
            *(s32 *)(D_0042BB80 + 0xE8) = e8;
            if (e8 == -1) {
                func_00243A80(0, 0, 0);
                *(s32 *)(D_003876A4 + 0x45C) = *(s32 *)(D_0042BB80 + 0xD4);
                *(s32 *)(D_003876A4 + 0x460) = *(s32 *)(D_0042BB80 + 0xD8);
            }
        } else {
            func_00419F68(&flag);
        }
    }

    if (flag) {
        s3 = 0;
        if (*(s32 *)(D_003876A4 + 0x1C) == 0x22) {
            s5 = 0;
            s6 = 4;
        } else {
            s5 = 5;
            s6 = 5;
        }

        A = D_0042BB80;
        if (*(s32 *)(A + 0xD8) == 0) {
            func_00325370((s32)GetTimerSystemTime());
            do {
                r = rand() % *(s32 *)(A + 0x144);
                s0 = r;
            } while (s0 == 0 || s0 == 2);
            s0 = *(s32 *)(*(u8 **)(A + 0x140) + 8 * r) - 1;
        } else {
            s0 = *(s32 *)(*(u8 **)(A + 0x140) + 8 * *(s32 *)(A + 0xD8) - 8) - 1;
        }

        if (*(s32 *)(D_003876A4 + 0x1C) == 0x22) {
            h = D_00387F2C;
            cs = *(s32 *)(h + 0x80C);
            if ((u32)cs < 5) {
                switch (cs) {
                case 0:
                    s3 = 1;
                    break;
                case 1:
                    s3 = 2;
                    break;
                case 2:
                    s3 = 3;
                    break;
                case 3:
                    s3 = 4;
                    break;
                default:
                    s3 = 0;
                    break;
                }
            }
        }

        if (*(s32 *)(A + 0xD0) & 8) {
            func_00325370((s32)GetTimerSystemTime());
            do {
                r = rand() % *(s32 *)(A + 0x13C);
                slot = A + 0xF0 + 4 * r;
            } while (*(s32 *)(slot + 0xC) == 7);
            t1v = func_0024AF50(*(s32 *)(slot + 0xC));
        } else {
            t1v = func_0024AF50(*(s32 *)(A + 0xFC + 4 * *(s32 *)(A + 0xD4)));
        }

        h = D_00387F2C;
        func_00101A60(s5, s0, s3, *(s32 *)(h + 0x820), s6, t1v);
    }

    func_004197B0();
    func_0028B218();
    return flag;
}
