#include "common.h"

void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void EftShotFx_UpdateReqs(void);
void EftShotFx_UpdateLines(void);
void func_0029D5C8(s32 arg0);
void func_0029D548(void);
void func_0029D580(s32 arg0);
void *func_00269A40(s32 arg0, s32 arg1);
void Vu0Cur_StoreMtx(s32 arg0, s32 arg1);
void func_00260928(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void sceVu0MulMatrix(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);

void func_00260D48(u8 *arg0) {
    u8 sp[0x60];
    s32 sp50;
    s32 sp54;
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *s7;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 bit;
    s32 pbit;

    sp54 = (s32)(arg0 + 0xAC0);
    s6 = 0;
    s7 = arg0 + 0x9A0;
    s1 = *(u8 **)(arg0 + 0x48);
    func_00312650((s32)sp, (s32)(arg0 + 0x9D0), sp54);
    EftShotFx_UpdateReqs();
    EftShotFx_UpdateLines();
    func_0029D5C8((s32)(arg0 + 0xA00));
    s4 = (*(u8 *)(arg0 + 0xAEC) != 0);
    sp50 = (s32)(arg0 + 0xD20);

    for (;;) {
        s6 += 1;
        s5 = 0;
        s0 = (u8 *)func_00269A40((s32)arg0, *(u16 *)(s1 + 0xA));
        func_0029D548();
        bit = 1 << s6;
        pbit = 1 << (s6 - 1);
        s4 &= ~bit;
        s3 = s0 + 0x40;
        if ((*(s32 *)(s0 + 0xD0) & 1) && (s4 & pbit)) {
            s4 |= bit;
            s5 = 1;
        }
        Vu0Cur_StoreMtx((s32)s3, bit);
        if (s5 != 0) {
            *(f32 *)(s0 + 0x30) = *(f32 *)(s0 + 0x30) + *(f32 *)(sp + 0x00);
            *(f32 *)(s0 + 0x34) = *(f32 *)(s0 + 0x34) + *(f32 *)(sp + 0x04);
            *(f32 *)(s0 + 0x38) = *(f32 *)(s0 + 0x38) + *(f32 *)(sp + 0x08);
        } else {
            func_00260928((s32)arg0, (s32)(sp + 0x10), (s32)s0, sp50);
            *(f32 *)(sp + 0x40) = *(f32 *)(s0 + 0x80);
            *(f32 *)(sp + 0x44) = *(f32 *)(s0 + 0x84);
            *(f32 *)(sp + 0x48) = *(f32 *)(s0 + 0x88);
            sceVu0MulMatrix((s32)s0, (s32)s3, (s32)(sp + 0x10));
        }
        func_0029D5C8((s32)s0);
        *(s32 *)(s0 + 0xD0) = *(s32 *)(s0 + 0xD0) | 1;
        if (*(u16 *)(s1 + 4) != 0) {
            func_0029D580(*(u16 *)(s1 + 4));
            s6 -= *(u16 *)(s1 + 4);
        }
        if (*(u16 *)(s1 + 6) == 0) {
            s1 += *(s32 *)s1;
            continue;
        }
        break;
    }

    {
        u8 *p;
        p = (u8 *)func_00269A40((s32)arg0, 0);
        func_003126C8((s32)(arg0 + 0x9C0), (s32)(p + 0x30));
    }
    s0 = arg0 + 0xA80;
    sceVu0CopyMatrix((s32)s0, (s32)(s7 + 0x60));
    s1 = arg0 + 0xBD0;
    func_003126C8(sp54, (s32)(s7 + 0x30));
    func_003126C8((s32)(arg0 + 0xAD0), (s32)(s7 + 0x40));
    *(u16 *)(s0 + 0x60) = *(u16 *)(s1 + 4);
    *(u16 *)(s0 + 0x62) = *(u16 *)(s1 + 6);
    *(f32 *)(s0 + 0x64) = *(f32 *)(s1 + 0x1C);
    *(u8 *)(s0 + 0x6C) = 1;
    *(f32 *)(s0 + 0x68) = *(f32 *)(s1 + 0x24);
}
