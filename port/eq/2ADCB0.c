#include "common.h"

extern u8 *D_00387E18;
extern u8 *D_003876A0;

u8 *func_002B1DD0(s32 arg0);
s32 func_002ACE38(void);
void func_002B0DC0(void *arg0);
void func_003126C8(void *arg0, void *arg1);
void func_002B0480(void *arg0);
void func_002B0A10(void *arg0);
void func_002AFFC0(void *arg0);
void func_002AF490(void *arg0);
void func_002B14E0(void *arg0);
void func_002B1778(void *arg0);
void func_002B16F8(void *arg0);
void func_002B1918(void *arg0);
void func_002B0E40(void *arg0);
void func_00312650(void *arg0, void *arg1, void *arg2);
void func_00260BF8(void *arg0, void *arg1);
void func_0025F2A0(void *arg0);
void func_0025F5F8(void *arg0);
void func_00260D48(void *arg0);
void func_0026A360(void *arg0, void *arg1);
void BtlMove_UpdateAction(void *arg0);
void func_00260638(void *arg0);
void func_002AF948(void *arg0);
void func_002AFBF8(void *arg0);
void func_002AFC28(void *arg0);
void func_002B1CB8(void *arg0);
void func_002B2398(void *arg0);
void func_002B2188(void);

void func_002ADCB0(void) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s4;
    s32 s3;

    if (D_00387E18 == NULL) {
        return;
    }
    if (*(s32 *)D_00387E18 == 0) {
        return;
    }
    if (*(s32 *)(D_00387E18 + 4) <= 0) {
        return;
    }
    *(u8 *)(D_00387E18 + 9) = 0;

    if (*(s32 *)(D_00387E18 + 4) > 0) {
        s3 = 0;
        do {
            s0 = func_002B1DD0(s3);
            s3 += 1;
            s4 = s0 + 0x130;
            s2 = s0 + 0x120;
            s1 = s0 + 0xD0;
            if (*(u8 *)(s0 + 0x20) != 0) {
                func_002B0DC0(s0);
                *(u8 *)(s0 + 0x190) = 0;
                func_003126C8(s2, s1);
                *(f32 *)(*(u8 **)s0 + 0xBE8) = 2.0f;
                *(s32 *)(s0 + 0x28) = *(s32 *)(s0 + 0x24);
                *(f32 *)(s0 + 0x150) = 1.0f;
                *(s32 *)(s0 + 0x170) = 0;
                *(s32 *)(s0 + 0x24) = 0;
                *(s32 *)(s0 + 0x2C) = 0;
                *(s32 *)(s0 + 0x30) = 0;
                *(u8 *)(s0 + 0x7D) = 0;
                *(u8 *)(s0 + 0x21) = 0;
                func_002B0480(s0);
                func_002B0A10(s0);
                func_002AFFC0(s0);
                func_002AF490(s0);
                if ((*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 22)) != 0) {
                    func_002B14E0(s0);
                    func_002B1778(s0);
                } else {
                    func_002B16F8(s0);
                    func_002B1918(s0);
                }
                func_002B0E40(s0);
                func_00312650(s4, s1, s2);
                func_00260BF8(*(void **)s0, (void *)0);
                func_0025F2A0(*(void **)s0);
                func_0025F5F8(*(void **)s0);
                func_00260D48(*(void **)s0);
                func_0026A360(*(void **)s0, s4);
                BtlMove_UpdateAction(*(void **)s0);
                func_00260D48(*(void **)s0);
                func_00260638(*(void **)s0);
                func_002B0DC0(s0);
                func_00312650(s0 + 0x140, s1, s2);
                func_002AF948(s0);
            }
        } while (s3 < *(s32 *)(D_00387E18 + 4));
    }

    if (func_002ACE38() == 0) {
        func_002AFBF8(func_002B1DD0(0));
    }

    if (*(s32 *)(D_00387E18 + 4) > 0) {
        s3 = 0;
        do {
            s0 = func_002B1DD0(s3);
            s3 += 1;
            if (*(u8 *)(s0 + 0x20) != 0) {
                func_002AFC28(s0);
                func_002B1CB8(s0);
                func_002B2398(s0);
            }
        } while (s3 < *(s32 *)(D_00387E18 + 4));
    }

    func_002B2188();
}
