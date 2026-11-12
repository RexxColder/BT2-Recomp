#include "common.h"

s32 scePad2GetState(s32 arg0);
s32 scePad2GetButtonProfile(s32 arg0, s32 arg1);
s32 scePad2Read(s32 arg0, s32 arg1);
s32 func_0028C4B8(s32 arg0, s32 arg1);
void func_0028C7D8(void);
void func_0028C890(void);
void *memset(void *arg0, s32 arg1, u32 arg2);

extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_003B0C14[] __attribute__((section(".data")));
extern u8 D_003B0C38[] __attribute__((section(".data")));

void func_0028BDA0(void) {
    u8 *fp;
    u8 *s0;
    u8 *s2;
    u8 *sp0;
    u8 *sp4;
    s32 s3;
    s32 s7;
    s32 v0;
    s32 mode;
    s32 var_a1;
    s32 read;
    s32 tv;
    s32 old10;
    s32 t;

    fp = D_003B0B00;
    sp0 = fp + 0x130;
    sp4 = fp + 0x134;
    s0 = fp + 0x140;
    s3 = 0;
    s7 = 0;
    do {
        v0 = scePad2GetState(*(s32 *)(s0 - 0x40));
        *(s32 *)(s0 - 0x3C) = v0;
        if (v0 == 1) {
            mode = *(s32 *)(s0 - 0x38);
            switch (mode) {
            case 0:
                func_0028C7D8();
                /* fallthrough */
            case 1:
                v0 = scePad2GetButtonProfile(*(s32 *)(s0 - 0x40), (s32)(fp + s3 + 0x10C));
                *(s32 *)(s0 - 0x30) = v0;
                if (v0 >= 0) {
                    *(s32 *)(s0 - 0x38) = *(s32 *)(s0 - 0x38) + 1;
                }
                break;
            case 2:
                read = scePad2Read(*(s32 *)(s0 - 0x40), s3 + (s32)D_003B0C14);
                tv = ((((s32)*(u8 *)(s0 - 0x2B)) << 8) | (s32)*(u8 *)(s0 - 0x2C)) ^ 0xFFFF;
                old10 = *(s32 *)(s0 - 0x10);
                *(s32 *)(s0 - 0x18) = read;
                *(s32 *)(s0 - 0xC) = tv & ~old10;
                *(s32 *)(s0 - 0x14) = tv;
                *(s32 *)(s0 - 0x10) = tv;
                var_a1 = *(s32 *)(s0 + 0);
                if ((var_a1 == tv) && (var_a1 != 0)) {
                    if (*(s32 *)(s0 - 0x8) != 0) {
                        *(s32 *)(sp0 + 8) = *(s32 *)(s0 - 0x8) - 1;
                        *(s32 *)(s0 + 4) = 0;
                    } else if (*(s32 *)(s0 - 0x4) == 0) {
                        *(s32 *)(s0 + 4) = var_a1;
                        *(s32 *)(s0 - 0x4) = 1;
                    } else {
                        t = *(s32 *)(s0 - 0x4) - 1;
                        *(s32 *)(sp4 + 8) = t;
                        *(s32 *)(s0 + 4) = 0;
                    }
                } else {
                    *(s32 *)(s0 + 0) = 0;
                    *(s32 *)(s0 + 4) = 0;
                }
                s2 = fp + s3 + 0x130;
                if (*(s32 *)(s2 + 4) != 0) {
                    var_a1 = 0xA;
                    *(s32 *)(fp + s3 + 0x140 + 0) = *(s32 *)(s2 + 4);
                    *(s32 *)(fp + s3 + 0x140 + 4) = *(s32 *)(s2 + 4);
                    *(s32 *)(s2 + 8) = 0xA;
                    *(s32 *)(fp + s3 + 0x13C) = 1;
                }
                if (func_0028C4B8(s7, var_a1) != 0) {
                    memset(D_003B0C14 + s3, 0, 0x12);
                    memset(D_003B0C38 + s3, 0, 8);
                    *(u8 *)(fp + s3 + 0x114) = 0xFF;
                    *(u8 *)(fp + s3 + 0x115) = 0xFF;
                    *(u8 *)(fp + s3 + 0x116) = 0x80;
                    *(u8 *)(fp + s3 + 0x117) = 0x80;
                    *(u8 *)(fp + s3 + 0x118) = 0x80;
                    *(u8 *)(fp + s3 + 0x119) = 0x80;
                    *(s32 *)(fp + s3 + 0x12C) = 0;
                    *(s32 *)(s2 + 4) = 0;
                    *(s32 *)(s2 + 0) = 0;
                    *(s32 *)(fp + s3 + 0x140 + 4) = 0;
                    *(s32 *)(fp + s3 + 0x140 + 0) = 0;
                }
                break;
            default:
                break;
            }
        } else {
            *(s32 *)(s0 - 0x38) = 0;
            memset(D_003B0C14 + s3, 0, 0x12);
            memset(D_003B0C38 + s3, 0, 8);
            *(u8 *)(s0 - 0x2C) = 0xFF;
            *(u8 *)(s0 - 0x2B) = 0xFF;
            *(u8 *)(s0 - 0x2A) = 0x80;
            *(u8 *)(s0 - 0x29) = 0x80;
            *(u8 *)(s0 - 0x28) = 0x80;
            *(u8 *)(s0 - 0x27) = 0x80;
            *(s32 *)(s0 - 0x14) = 0;
            *(s32 *)(s0 - 0x10) = 0;
            *(s32 *)(s0 - 0xC) = 0;
            *(s32 *)(s0 + 0) = 0;
            *(s32 *)(s0 + 4) = 0;
        }
        s7 += 1;
        s0 += 0x180;
        s3 += 0x180;
        sp0 += 0x180;
        sp4 += 0x180;
    } while (s7 < 2);
    func_0028C890();
}
