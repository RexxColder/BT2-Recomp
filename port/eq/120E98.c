#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define LU8(p, off) (*(u8 *)((u8 *)(p) + (off)))

s32 func_0011FAE0(s32 arg0, s32 arg1, s32 arg2);

extern u8 *D_003876A0;

/* 0x00120E98: queues up to eight entries (bytes 0x10..0x17 of the record at arg1 * 32 of the table at +0x11D4,
 * skipping 0xFF) through func_0011FAE0, after a per-mode prologue of 0x76/0x77 calls for modes 0..3. The
 * prologue is skipped when the table count at +0x11D0 is not above arg1, or when the global's +0xB8 is 4. */
void func_00120E98(s32 arg0, s32 arg1) {
    u8 *p;
    u8 *a;
    u8 *b;
    u8 *s3;
    s32 mode;
    s32 k;
    u8 c;

    p = (u8 *)(s32)arg0;
    a = (u8 *)(s32)LD32(p, 0x11D0);
    if (a == NULL) {
        return;
    }
    b = (u8 *)(s32)LD32(p, 0x11D4);
    if (b == NULL) {
        return;
    }
    if (!(arg1 < LD32(a, 0))) {
        return;
    }

    s3 = b + (arg1 << 5);
    if (LD32(D_003876A0, 0xB8) != 4) {
        mode = LD32(p, 0x8);
        if ((u32)mode < 5) {
            switch (mode) {
            case 0:
                func_0011FAE0(arg0, 0x76, 0);
                func_0011FAE0(arg0, 0x76, 0);
                func_0011FAE0(arg0, 0x77, 0);
                func_0011FAE0(arg0, 0x77, 0);
                func_0011FAE0(arg0, 0x76, 0);
                func_0011FAE0(arg0, 0x76, 0);
                break;
            case 1:
                func_0011FAE0(arg0, 0x77, 0);
                func_0011FAE0(arg0, 0x76, 0);
                func_0011FAE0(arg0, 0x76, 0);
                break;
            case 2:
                func_0011FAE0(arg0, 0x76, 0);
                func_0011FAE0(arg0, 0x76, 0);
                break;
            case 3:
                func_0011FAE0(arg0, 0x76, 0);
                break;
            default:
                break;
            }
        }
    }

    for (k = 0; k < 8; k++) {
        c = LU8(s3, 0x10 + k);
        if (c != 0xFF) {
            func_0011FAE0(arg0, c, LD32(s3, 0x1C));
        }
    }
}
