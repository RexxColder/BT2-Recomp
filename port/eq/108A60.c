#include "common.h"

#define U16AT(p) (*(u16 *)(p))

s32 BtlText_IsNewline(s32);
s32 func_00108780(s32, s32, s32, s32, s32, s32);
extern u8 D_0033FFB8[] __attribute__((section(".data")));

s32 func_00108A60(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    u8 *s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 a3;
    s32 n;
    u16 c;

    s1 = (u8 *)arg3;
    s2 = 0;
    s3 = arg1;
    s4 = arg0;

    for (;;) {
        c = U16AT(s1);
        if (c == 0 || BtlText_IsNewline(c) != 0) {
            break;
        }
        a3 = 0x20;
        switch (c) {
        case 0x2190:
            s2 = 6;
            break;
        case 0x2191:
            s2 = 4;
            break;
        case 0x2192:
            s2 = 7;
            break;
        case 0x2193:
            s2 = 5;
            break;
        case 0x25CB:
            s2 = 8;
            break;
        case 0x25A1:
            s2 = 9;
            n = U16AT(s1 + 2);
            if (n == 0x2A || n == 0xFF0A) {
                s2 = 0x12;
                a3 = 0x40;
                s1 += 2;
            }
            break;
        case 0xD7:
            s2 = 0xA;
            break;
        case 0x25B3:
            s2 = 0xB;
            break;
        case 0xFF2C:
        case 0x4C:
            n = U16AT(s1 + 2);
            switch (n) {
            case 0x31:
                s2 = 0xC;
                break;
            case 0x32:
                s2 = 0xD;
                break;
            case 0xFF11:
                s2 = 0xC;
                break;
            case 0xFF13:
                s2 = 0xE;
                break;
            case 0xFF12:
                s2 = 0xD;
                break;
            case 0x33:
                s2 = 0xE;
                break;
            }
            s1 += 2;
            break;
        case 0xFF32:
        case 0x52:
            n = U16AT(s1 + 2);
            switch (n) {
            case 0x31:
                s2 = 0xF;
                break;
            case 0x32:
                s2 = 0x10;
                break;
            case 0xFF11:
                s2 = 0xF;
                break;
            case 0xFF12:
                s2 = 0x10;
                break;
            case 0x33:
            case 0xFF13:
                s2 = 0x11;
                break;
            }
            s1 += 2;
            break;
        case 0xFF0B:
            s2 = 0;
            break;
        case 0xFF0F:
            s2 = 1;
            break;
        case 0xFF08:
            s2 = 2;
            break;
        case 0xFF09:
            s2 = 3;
            break;
        default:
            /* unmatched characters keep the previous s2 (as the asm does) */
            break;
        }
        s1 += 2;
        n = s2 * 2;
        s4 = func_00108780(s4, s3 + (s8)D_0033FFB8[n], arg2, a3, 0x20, s2);
        s3 += (s8)D_0033FFB8[n + 1] + 3;
    }
    return s4;
}
